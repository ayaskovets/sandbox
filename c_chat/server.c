#include "server.h"

#include <stddef.h>
#include <string.h>

#include <sys/socket.h>

#include <arpa/inet.h>

#include <errno.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>

#include "log.h"
#include "dns.h"
#include "storage.h"
#include "threading.h"


bool tcp_server(const char *hostname, const char *port) {
    int sock, peersock;
    struct sockaddr_storage addr, peeraddr;
    socklen_t peeraddrlen = sizeof(peeraddr);
    char ip[INET6_ADDRSTRLEN], peerip[INET6_ADDRSTRLEN];
    int peerport;
    pthread_t recvthread;
    char sendbuf[128];
    int sendbuflen;
    int enable = 1;

    /* resolve hostname */
    if (!resolve_hostname(hostname, port, SOCK_STREAM, AI_PASSIVE, &addr)) {
        ERROR("failed to resolve hostname %s", hostname);
        return false;
    }

    /* get logging info */
    if (!get_ip(&addr, ip)) {
        ERROR("failed to parse ip from %s", hostname);
        return false;
    }
    INFO("resolved hostname %s to %s", hostname, ip);

    /* create TCP socket */
    sock = socket(addr.ss_family, SOCK_STREAM, 0);
    if (sock == -1) {
        ERROR("%s", strerror(errno));
        return false;
    }
    INFO("%s", "created a new TCP server socket");

    /* set socket options */
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable,
                   sizeof(enable)) == -1) {
        ERROR("%s", "failed to set SO_REUSEADDR");
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &enable,
                   sizeof(enable)) == -1) {
        ERROR("%s", "failed to set SO_REUSEPORT");
    }

    /* bind the socket to the ip:port */
    if (bind(sock, (const struct sockaddr *)&addr, addr.ss_len) == -1) {
        ERROR("%s", strerror(errno));
        return false;
    }
    INFO("bound %s:%s", ip, port);

    /* mark the socket as accepting one incoming connection */
    if (listen(sock, 1) == -1) {
        ERROR("%s", strerror(errno));
        return false;
    }
    INFO("listening on %s:%s", ip, port);

    /* accept a new connection on the socket */
    peersock = accept(sock, (struct sockaddr *)&peeraddr,
                      &peeraddrlen);
    if (peersock == -1) {
        ERROR("%s", strerror(errno));
        return false;
    }

    /* get peer logging info */
    if (!get_ip(&peeraddr, peerip) || !get_port(&peeraddr, &peerport)) {
        ERROR("%s", "failed to parse peer ip and port");
        return false;
    }
    INFO("accepted connection from %s:%d", peerip, peerport);

    /* spin up the receiver thread */
    if (!recv_thread(&peersock, &recvthread)) {
        ERROR("%s", "failed start the receiver thread");
        return false;
    }

    /* start the sender loop */
    while (fgets(sendbuf, sizeof(sendbuf), stdin)) {
        sendbuflen = strnlen(sendbuf, sizeof(sendbuf));
        if (sendbuflen == 1) {
            continue;
        }

        if (send(peersock, sendbuf, sendbuflen - 1, 0) == -1) {
            ERROR("%s", strerror(errno));
            break;
        }
    }

    /* free up the resources */
    if (close(sock) == -1) {
        ERROR("%s", strerror(errno));
        return false;
    }
    if (close(peersock) == -1) {
        ERROR("%s", strerror(errno));
        return false;
    }
    INFO("%s", "closed both sockets");

    /* cancel the thread */
    if (pthread_cancel(recvthread) != 0) {
        ERROR("%s", "failed to stop the receiver thread");
        return false;
    }

    return true;
}
