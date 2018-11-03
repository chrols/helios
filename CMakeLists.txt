cmake_minimum_required(VERSION 2.8.11)

project(raytracer)

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -std=c++1z")

include_directories(include)

FILE(GLOB SOURCE_FILES src/*.cpp)
FILE(GLOB TEST_FILES test/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libgtest.a)

find_package( OpenMP )
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

