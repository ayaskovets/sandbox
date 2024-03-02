#pragma once

#include <stdbool.h>

#include <pthread.h>


bool recv_thread(const int *sock, pthread_t *pthread);
