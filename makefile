CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC_DIR = src
TARGET = $(SRC_DIR)/main

SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/scene.cpp \
      $(SRC_DIR)/vec.cpp

OBJ = $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)