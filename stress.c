#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

// stress creates a file with given size and loads it into memory
// Usage: stress <size in bytes>

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

int main(int argc, char *argv[]) {
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
        buffer[i] = 'A'; // Fill with dummy data
    }

    printf("Allocated and filled %ld bytes of memory.\n", size);

    // wait for SIGABRT or SIGINT to terminate
    printf("Press Ctrl+C to terminate...\n");
    while (1) {}

    free(buffer);
    exit(EXIT_SUCCESS);
}
