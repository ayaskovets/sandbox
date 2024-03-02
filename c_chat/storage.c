#include "storage.h"

#include <arpa/inet.h>

#include "log.h"


bool get_ip(const struct sockaddr_storage *storage, char *ip) {
    /* parse ip from the corresponding sockaddr */
    switch (storage->ss_family) {
    case AF_INET:
        inet_ntop(AF_INET,
                  &((const struct sockaddr_in*)storage)->sin_addr, ip,
                  ((const struct sockaddr_in*)storage)->sin_len);
        return true;
    case AF_INET6:
        inet_ntop(AF_INET6,
                  &((const struct sockaddr_in6*)storage)->sin6_addr, ip,
                  ((const struct sockaddr_in6*)storage)->sin6_len);
        return true;
    default:
        ERROR("invalid address family %d", storage->ss_family);
        return false;
    }
}

bool get_port(const struct sockaddr_storage *storage, int *port) {
    /* parse port from the corresponding sockaddr */
    switch (storage->ss_family) {
    case AF_INET:
        *port = ntohs(((const struct sockaddr_in*)storage)->sin_port);
        return true;
    case AF_INET6:
        *port = ntohs(((const struct sockaddr_in6*)storage)->sin6_port);
        return true;
    default:
        ERROR("invalid address family %d", storage->ss_family);
        return false;
    }
}
