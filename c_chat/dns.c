#include "dns.h"

#include <stddef.h>
#include <string.h>

#include <sys/socket.h>

#include <errno.h>
#include <netdb.h>
#include <unistd.h>

#include "log.h"


bool resolve_hostname(const char *hostname, const char *port, int socktype,
                      int flags, struct sockaddr_storage* storage) {
    int sock;
    struct addrinfo *result, *rp, hints;
    int error;

    /* prepare hints for IPv4 or IPv6 address */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = socktype;
    hints.ai_flags = flags;

    /* call gai */
    switch ((error = getaddrinfo(hostname, port, &hints, &result))) {
    case 0:
        break;
    case EAI_SYSTEM:
        ERROR("could not resolve %s: %s", hostname, strerror(errno));
        return false;
    default:
        ERROR("could not resolve %s: %s", hostname, gai_strerror(error));
        return false;
    }

    /* find the first valid address */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sock == -1) {
            continue;
        }

        close(sock);
        memcpy(storage, rp->ai_addr, rp->ai_addrlen);
        freeaddrinfo(result);
        return true;
    }

    return false;
}
