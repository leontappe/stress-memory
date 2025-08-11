#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>

size_t parse_size(const char *str);

void sleep_seconds(double seconds);

#endif // UTIL_H