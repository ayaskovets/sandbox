#pragma once

#include <stdbool.h>

#include <sys/socket.h>


bool resolve_hostname(const char *hostname, const char *port, int socktype,
                      int flags, struct sockaddr_storage* storage);
