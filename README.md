# Stress Memory

A lightweight C program suite for stress testing system memory allocation and usage.

## Overview

This project provides two command-line utilities for memory stress testing:

- **`stress`** - Allocates memory using `malloc()` and fills it with dummy data
- **`stress-file`** - Creates a temporary file and maps it into memory using `mmap()`

Both are useful for:
- Testing system memory limits
- Simulating memory-intensive applications
- Load testing in containerized environments
- Memory stress testing scenarios
- Testing different memory allocation strategies

## Features

- Support for human-readable size formats (K, M, G, T suffixes)
- Cross-platform compatibility
- Lightweight and minimal dependencies
- Shared parsing logic between both programs
- Docker support for containerized testing
- Two different memory allocation approaches

## Building

### Prerequisites
- GCC compiler
- Make (optional, for using Makefile)

### Compile with Make
```bash
# Build both programs
make

# Build only malloc version
make stress-only

# Build only file mapping version
make stress-file-only
```

### Compile manually
```bash
# Malloc version
gcc -Wall -Wextra -std=c99 -O2 -o stress stress.c parse.c

# File mapping version
gcc -Wall -Wextra -std=c99 -O2 -o stress-file stress-file.c parse.c
```

## Usage

### Memory Allocation Version
```bash
./stress <size>
```

### File Mapping Version
```bash
./stress-file <size>
```

### Size Format
Both programs accept the same size parameter format:
- Plain numbers (bytes): `1048576`
- With suffixes: `1M`, `512K`, `2G`, `1T`
- Optional 'B' suffix: `1MB`, `512KB`

### Examples
```bash
# Allocate 100MB using malloc
./stress 100M

# Create and map 1GB file into memory
./stress-file 1G

# Allocate exactly 1048576 bytes
./stress 1048576
./stress-file 1048576
```

## Program Behavior

### `stress` (malloc version)
1. Parse and validate the size parameter
2. Allocate memory using `malloc()`
3. Fill the memory with dummy data ('A' characters)
4. Display confirmation message
5. Wait indefinitely (press Ctrl+C to terminate)

### `stress-file` (mmap version)
1. Parse and validate the size parameter
2. Create a temporary file in `/tmp/`
3. Extend the file to the specified size
4. Fill the file with dummy data
5. Map the file into memory using `mmap()`
6. Touch all memory pages to load them into physical memory
7. Display confirmation message
8. Wait indefinitely (press Ctrl+C to terminate)
9. Cleanup temporary file on exit

## Docker

A Dockerfile is included for containerized usage.