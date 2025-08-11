#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "util.h"

// stress creates a file with given size and loads it into memory
// Usage: stress <size in bytes>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size in bytes>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    size_t size = parse_size(argv[1]);
    if (size == 0) {
        fprintf(stderr, "Invalid size specified.\n");
        exit(EXIT_FAILURE);
    }

    char* buffer = malloc(size);
    if (!buffer) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Simulate loading the file into memory
    for (size_t i = 0; i < size; i++) {
        buffer[i] = 'A';
    }

    printf("Allocated and filled %ld bytes of memory.\n", size);
    printf("Press Ctrl+C to terminate...\n");

    while (1) {
        printf("Processing data to keep addresses active...\n");
        for (size_t i = 0; i < size; i++) {
            // simplest toggle uppercase/lowercase ever
            if (buffer[i] < 0x61) buffer[i] = buffer[i] + 0x20;
            else buffer[i] = buffer[i] - 0x20;
        }
        sleep_seconds(5);
    }

    free(buffer);
    exit(EXIT_SUCCESS);

    return 0;
}
