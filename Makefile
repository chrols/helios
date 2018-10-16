TARGET_EXEC ?= raytracer

OBJ_DIR ?= obj
SRC_DIR ?= src
INC_DIR ?= include

SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.cpp=.o))
DEPS := $(OBJS:.o=.d)

TEST_DIR ?= ./test
TEST_SRCS := $(shell find $(TEST_DIR) -name *.cpp)
TEST_OBJS := $(patsubst $(TEST_DIR)/%,$(OBJ_DIR)/test/%,$(TEST_SRCS:.cpp=.o))

INC_FLAGS := -I $(INC_DIR)

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -fopenmp
CXXFLAGS ?= -std=c++1z -g # -Wall -Wextra
LDFLAGS ?= -pthread lib/libgtest.a -fopenmp

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TARGET_EXEC)-test: $(TARGET_EXEC) $(TEST_OBJS)
	$(CXX) $(OBJS) $(TEST_OBJS) -o $(TARGET_EXEC)-test $(LDFLAGS)

test: $(TARGET_EXEC)-test
	./$(TARGET_EXEC)-test -test

.PHONY: clean

clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(OBJ_DIR)/*.d
	$(RM) $(OBJ_DIR)/test/*.o
	$(RM) $(OBJ_DIR)/test/*.d
	$(RM) $(TARGET_EXEC)*

-include $(DEPS)

