CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Og -g -fsanitize=address,undefined

BUILD_DIR = build
TARGET = $(BUILD_DIR)/main
SRC = main.c

$(TARGET): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean
