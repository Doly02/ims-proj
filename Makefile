#   Project:        IMS Project - Electromobility in Brno
#   File Name:      Makefile
#   Author:         Tomas Dolak, Monika Zahradnikova
#   Date:           17.11.2024
#   Description:    Makefile for Model of Electromobility in Brno.

# Program Name
TARGET = sim
# Program Name For Debug Configuration
DEBUG_TARGET = sim_debug
# Test Program Name
TEST_TARGET = sim_test

# Compiler
CC = g++
# Compiler Flags
CFLAGS = -std=c++17 -Wall -Wextra -Iinclude
DEBUG_CFLAGS = -fsanitize=address -g -std=c++17 -Wall -Wextra -Werror -Wshadow -Wnon-virtual-dtor -pedantic

# Header Files
HEADERS = include/definitions.hpp include/ElectricVehicle.hpp include/GeneratorDay.hpp

# Libraries
LIBS = -lm -lsimlib

# Source Files
SOURCES = src/ElectricVehicle.cpp src/GeneratorDay.cpp src/main.cpp
# Object Files 
OBJECTS = $(SOURCES:.cpp=.o)

# Test Source Files
TEST_SOURCES = tests/main.cpp
# Test Object Files (Derived from TEST_SOURCES)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
# Google Test Flags
GTEST_FLAGS = -lgtest -lgtest_main -pthread
# Default build target
all: $(TARGET)

# Main target
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	rm -f $(OBJECTS)

# Object compilation
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_OBJECTS) $(TEST_TARGET)