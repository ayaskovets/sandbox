#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include "client.h"
#include "server.h"


#define TCP "tcp"
#define UDP "udp"

void usage() {
    fprintf(stderr, "usage: chat [-c] [-p protocol] [hostname] [port]\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    int opt;
    bool is_server = true;
    const char *protocol = TCP, *hostname, *port;

    if (argc < 3) {
        usage();
    }

    while ((opt = getopt(argc, argv, "cp:")) != -1) {
        switch (opt) {
        case 'p':
            if (!strncmp(optarg, TCP, sizeof(TCP) - 1)) {
                protocol = TCP;
            } else if (!strncmp(optarg, UDP, sizeof(UDP) - 1)) {
                protocol = UDP;
            } else {
                usage();
            }
            break;
        case 'c':
            is_server = false;
            break;
        default:
            usage();
        }
    }

    if (optind + 1 >= argc) {
        usage();
    } else {
        hostname = argv[optind];
        port = argv[optind + 1];
    }

    if (!strncmp(protocol, TCP, sizeof(TCP) - 1)) {
        return (is_server ? tcp_server : tcp_client)(hostname, port);
    } else if (!strncmp(protocol, UDP, sizeof(UDP) - 1)) {
        // return (is_server ? udp_server : udp_client)(hostname, port);
    } else {
        usage();
    }

    return 0;
}