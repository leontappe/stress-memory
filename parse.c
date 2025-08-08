#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

size_t parse_size(const char *str) {
    char *endptr;
    errno = 0;
    unsigned long long value = strtoull(str, &endptr, 10);

    if (errno != 0) {
        perror("strtoull");
        return 0;
    }

    // Skip whitespace
    while (isspace((unsigned char)*endptr)) endptr++;

    size_t multiplier = 1;
    if (*endptr != '\0') {
        switch (toupper((unsigned char)*endptr)) {
            case 'K': multiplier = 1024ULL; break;
            case 'M': multiplier = 1024ULL * 1024ULL; break;
            case 'G': multiplier = 1024ULL * 1024ULL * 1024ULL; break;
            case 'T': multiplier = 1024ULL * 1024ULL * 1024ULL * 1024ULL; break;
            default:
                fprintf(stderr, "Unknown size suffix: %c\n", *endptr);
                return 0;
        }
        endptr++;
        // Allow for a trailing 'B' (e.g., 1MB)
        if (toupper((unsigned char)*endptr) == 'B') endptr++;
        // Skip trailing whitespace
        while (isspace((unsigned char)*endptr)) endptr++;
        if (*endptr != '\0') {
            fprintf(stderr, "Unexpected characters after size: '%s'\n", endptr);
            return 0;
        }
    }

    return (size_t)(value * multiplier);
}