#pragma once

#include <stdbool.h>

bool tcp_client(const char* hostname, const char *port);
bool udp_client(const char* hostname, const char *port);
