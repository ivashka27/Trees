CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Itrees/include
LDFLAGS =

SRC = src/AVLTree.cpp tests/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = test_avl

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all test clean
