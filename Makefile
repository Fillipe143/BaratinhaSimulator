.SILENT:

CXX = g++
CXXFLAGS = -std=c++20 -Wall -lSDL2

SRCS = src/*.cpp src/lib/*.cpp src/arduino/*.cpp
TARGET = bin/baratinha_simulator

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: build
	./$(TARGET)
