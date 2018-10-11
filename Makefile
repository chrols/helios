# SRC_DIR := .../src
# OBJ_DIR := .../obj
# SRC_FILES := 
# OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
# LDFLAGS := ...
# CPPFLAGS := ...
# CXXFLAGS := ...

# raytracer: $(OBJ_FILES)
#    g++ $(LDFLAGS) -o $@ $^

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
#    g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

SRC = $(wildcard *.cpp)
TEST = $(wildcard test/*.cpp)

all: $(SRC)
	g++ $(SRC) $(TEST) -o raytracer libgtest.a -pthread
	./raytracer
