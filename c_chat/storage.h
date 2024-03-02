#pragma once

#include <stdbool.h>

#include <sys/socket.h>


bool get_ip(const struct sockaddr_storage *storage, char *ip);
bool get_port(const struct sockaddr_storage *storage, int *port);
