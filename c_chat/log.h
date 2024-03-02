#pragma once

#include <stdio.h>


#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define RESET "\033[0m"

#define LOG(level, color, fmt, ...)\
    fprintf(stderr, color level " %s::(%d): " RESET fmt "\n",\
            __func__, __LINE__, __VA_ARGS__);

#define ERROR(fmt, ...)\
    LOG("ERROR", KRED, fmt, __VA_ARGS__)

#define INFO(fmt, ...)\
    LOG("INFO", KGRN, fmt, __VA_ARGS__)

#define CHAT(len, message)\
    fprintf(stdout, KYEL "chat[%d]::" RESET "%*.*s\n", len, len, len, message)
