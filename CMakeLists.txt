cmake_minimum_required(VERSION 2.8.11)

project(raytracer)

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -std=c++1z -Wall -Werror")

include_directories(include)

FILE(GLOB SOURCE_FILES src/*.cpp)
FILE(GLOB TEST_FILES test/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

list(FILTER SOURCE_FILES EXCLUDE REGEX "main.cpp$")

add_definitions(-DUNITTEST)
add_executable(${PROJECT_NAME}-test ${SOURCE_FILES} ${TEST_FILES})

set(UNIT_TEST ${PROJECT_NAME}-test)
add_custom_command(
     TARGET ${UNIT_TEST}
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${PROJECT_NAME}-test --use-colour no
)

find_package( OpenMP )
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

