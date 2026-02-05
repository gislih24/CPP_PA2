CXX := g++
CXXFLAGS := -std=c++98 -O2 -Wall -Wextra -pedantic

TARGET := kattis_dll
SRCS := DoublyLinkedList.cpp kattis_dll_template.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp DoublyLinkedList.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
