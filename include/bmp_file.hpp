#pragma once

#include <fstream>

#include "canvas.hpp"

template <typename T>
void writeBytes(std::fstream &file, T data) {
    file.write(reinterpret_cast<char *>(&data), sizeof(T));
}

void writeBmpFile(const char *filename, const Canvas &canvas);
