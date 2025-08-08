CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = stress
SOURCE = stress.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Clean up compiled files
clean:
	rm -f $(TARGET)

# Install (optional - adjust path as needed)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall (optional)
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Force rebuild
rebuild: clean all

# Phony targets
.PHONY: all clean install uninstall rebuild
