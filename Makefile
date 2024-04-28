.SILENT:

CXX = g++
CXXFLAGS = -std=c++20 -Wall -lraylib

SRCS = src/*.cpp src/entities/*.cpp
TARGET = bin/baratinha_simulator

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: build
	./$(TARGET)
