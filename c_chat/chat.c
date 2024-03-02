#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include "client.h"
#include "server.h"


void usage() {
    fprintf(stderr, "usage: chat [-c] [hostname] [port]\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    int opt;
    bool is_server = true;
    const char *hostname, *port;

    if (argc < 3) {
        usage();
    }

    while ((opt = getopt(argc, argv, "cp:")) != -1) {
        switch (opt) {
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

    return !(is_server ? tcp_server : tcp_client)(hostname, port);
}