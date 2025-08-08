CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

# Source files
COMMON_SRC = parse.c
STRESS_SRC = stress.c
STRESS_FILE_SRC = stress-file.c

# Targets
TARGETS = stress stress-file
STRESS_TARGET = stress
STRESS_FILE_TARGET = stress-file

# Default target
all: $(TARGETS)

# Compile the memory allocation version
$(STRESS_TARGET): $(STRESS_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $(STRESS_TARGET) $(STRESS_SRC) $(COMMON_SRC)

# Compile the file mapping version
$(STRESS_FILE_TARGET): $(STRESS_FILE_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $(STRESS_FILE_TARGET) $(STRESS_FILE_SRC) $(COMMON_SRC)

# Clean up compiled files
clean:
	rm -f $(TARGETS)

# Install both programs (optional - adjust path as needed)
install: $(TARGETS)
	cp $(TARGETS) /usr/local/bin/

# Uninstall both programs (optional)
uninstall:
	rm -f /usr/local/bin/$(STRESS_TARGET) /usr/local/bin/$(STRESS_FILE_TARGET)

# Force rebuild
rebuild: clean all

# Individual targets for convenience
stress-only: $(STRESS_TARGET)
stress-file-only: $(STRESS_FILE_TARGET)

# Phony targets
.PHONY: all clean install uninstall rebuild stress-only stress-file-only
