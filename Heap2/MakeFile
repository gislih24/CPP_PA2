CXX := g++
CXXFLAGS := -std=c++98 -O2 -Wall -Wextra -pedantic
INCLUDES := -I.

BIN_DIR := bin
TARGET := heap2
SRC := kattis_heap2_template.cpp
HDR := Heap2.h

.PHONY: all build run clean

all: build

build: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(SRC) $(HDR)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

clean:
	rm -rf $(BIN_DIR)
