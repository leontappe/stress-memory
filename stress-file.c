#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

#include "util.h"
#include "config.h"

// stress-file creates a file with given size and maps it into memory
// Usage: stress-file <size in bytes>

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

    // Create temporary file
    char template[] = "/tmp/stress-XXXXXX";
    int fd = mkstemp(template);
    if (fd == -1) {
        perror("Failed to create temporary file");
        exit(EXIT_FAILURE);
    }

    printf("Created temporary file: %s\n", template);

    // Extend file to desired size
    if (ftruncate(fd, size) == -1) {
        perror("Failed to set file size");
        close(fd);
        unlink(template);
        exit(EXIT_FAILURE);
    }

    // Fill the file with dummy data
    printf("Writing %ld bytes to file...\n", size);
    char buffer[4096];
    memset(buffer, 'A', sizeof(buffer));

    size_t remaining = size;
    while (remaining > 0) {
        size_t to_write = (remaining < sizeof(buffer)) ? remaining : sizeof(buffer);
        ssize_t written = write(fd, buffer, to_write);
        if (written == -1) {
            perror("Failed to write to file");
            close(fd);
            unlink(template);
            exit(EXIT_FAILURE);
        }
        remaining -= written;
    }

    // Reset file position to beginning
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Failed to seek to beginning of file");
        close(fd);
        unlink(template);
        exit(EXIT_FAILURE);
    }

    // Map file into memory
    printf("Mapping file into memory...\n");
    void* mapped = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("Failed to map file into memory");
        close(fd);
        unlink(template);
        exit(EXIT_FAILURE);
    }

    printf("Successfully created file (%s)\n", template);
    printf("Press Ctrl+C to terminate...\n");

    // periodically touch the memory to keep it resident
    while (1) {
        printf("Loading pages into physical memory...\n");

        volatile char* ptr = (volatile char*)mapped;
        size_t page_size = getpagesize();
        for (size_t i = 0; i < size; i += page_size) {
            // Read from each page to force it into memory
            volatile char dummy = ptr[i];
            (void)dummy; // Suppress unused variable warning
        }

        // Touch the last byte if file size isn't page-aligned
        if (size > 0) {
            volatile char dummy = ptr[size - 1];
            (void)dummy;
        }

        sleep_seconds(MEMORY_KEEPALIVE_INTERVAL);
    }

    // Cleanup (this code won't be reached due to infinite loop above,
    // but good practice for signal handlers)
    munmap(mapped, size);
    close(fd);
    unlink(template);

    return 0;
}