#ifndef UTIL_H
#define UTIL_H

#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>

size_t parse_size(const char *str);

void sleep_seconds(double seconds);

#endif // UTIL_H