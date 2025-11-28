CXX := g++
CXXFLAGS := -std=c++11 -O3 -Wall
DEBUGFLAGS := -g -O0 -DDEBUG

SRCS := projeto25.cpp
TARGET := a.out

.PHONY: all debug clean run

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

debug: CXXFLAGS := $(CXXFLAGS) $(DEBUGFLAGS)
debug: clean $(TARGET)

run: $(TARGET)
	./$(TARGET) < testfile

clean:
	rm -f $(TARGET)
