# SRC_DIR := .../src
# OBJ_DIR := .../obj
# SRC_FILES := 
# OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
# LDFLAGS := ...
# CPPFLAGS := ...
CXXFLAGS := -std=c++1z -fopenmp

# raytracer: $(OBJ_FILES)
#    g++ $(LDFLAGS) -o $@ $^

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
#    g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

SRC = $(wildcard *.cpp)
TEST = $(wildcard test/*.cpp)

raytracer: $(SRC) $(TEST)
	g++  $(CXXFLAGS) $(SRC) $(TEST) -o raytracer libgtest.a -pthread -g

all: raytracer

test: raytracer
	./raytracer -test
