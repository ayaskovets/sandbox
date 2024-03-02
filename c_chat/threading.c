#include "threading.h"

#include <stddef.h>
#include <string.h>

#include <sys/socket.h>

#include <errno.h>

#include "log.h"


void *recv_func(void *sock) {
    char recvbuf[128];
    int recvbuflen;

    /* indefinitely receive data from socket */
    while (true) {
        switch (recvbuflen = recv(*(int *)sock, recvbuf, sizeof(recvbuf), 0)) {
        case 0:
            break;
        case -1:
            ERROR("%s", strerror(errno));
            return NULL;
        default:
            CHAT(recvbuflen, recvbuf);
            break;
        }
    }

    INFO("%s", "stopped the receiver thread");
    return NULL;
}

bool recv_thread(const int *sock, pthread_t *pthread) {
    if (pthread_create(pthread, NULL, recv_func, (int *)sock) != 0) {
        ERROR("%s", "failed to create the receiver thread");
        return false;
    }

    return true;
}

