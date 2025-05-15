CC      := gcc
CFLAGS  := -Wall -Wextra -pthread -Iinclude
LDFLAGS := 
SRC_DIR := src
INC_DIR := include
BUILD   := build
TARGET  := custom_wc

SRCS    := $(wildcard $(SRC_DIR)/*.c)
OBJS    := $(patsubst $(SRC_DIR)/%.c,$(BUILD)/%.o,$(SRCS))


all: $(BUILD) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD) $(TARGET)

.PHONY: all clean
