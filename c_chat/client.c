#include "client.h"

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


bool tcp_client(const char *hostname, const char *port) {
    int sock;
    struct sockaddr_storage addr;
    char ip[16];
    pthread_t recvthread;
    char sendbuf[128];
    int sendbuflen;

    /* resolve hostname */
    if (!resolve_hostname(hostname, port, SOCK_STREAM, 0, &addr)) {
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
    INFO("%s", "created a new TCP client socket");

    /* connect to the server */
    if (connect(sock, (const struct sockaddr *)&addr, addr.ss_len) == -1) {
        ERROR("%s", strerror(errno));
        return false;
    }
    INFO("connected to %s:%s", ip, port);

    /* spin up the receiver thread */
    if (!recv_thread(&sock, &recvthread)) {
        ERROR("%s", "failed start the receiver thread");
        return false;
    }

    /* start the sender loop */
    while (fgets(sendbuf, sizeof(sendbuf), stdin)) {
        sendbuflen = strnlen(sendbuf, sizeof(sendbuf));
        if (sendbuflen == 1) {
            continue;
        }

        if (send(sock, sendbuf, sendbuflen - 1, 0) == -1) {
            ERROR("%s", strerror(errno));
            break;
        }
    }

    /* free up the resources */
    if (close(sock) == -1) {
        ERROR("%s", strerror(errno));
        return false;
    }
    INFO("%s", "closed client socket");

    /* cancel the thread */
    if (pthread_cancel(recvthread) != 0) {
        ERROR("%s", "failed to stop the receiver thread");
        return false;
    }

    return true;
}
