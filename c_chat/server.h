#pragma once

#include <stdbool.h>

bool tcp_server(const char* hostname, const char *port);
bool udp_server(const char* hostname, const char *port);
