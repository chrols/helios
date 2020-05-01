#include "bmp_file.hpp"

#include <cstdint>
#include <fstream>

void writeBmpFile(const char *filename, const Canvas &canvas) {
    std::fstream file(filename, std::ios::binary | std::ios::out);
    // Magic
    file << 'B' << 'M';

    int pixels = canvas.width() * canvas.height();

    uint32_t fileSize = 54 + pixels * 4;
    uint32_t reserved = 0;
    uint32_t dataOffset = 54;
    uint32_t headerSize = 40;
    int32_t width = canvas.width();
    int32_t height = canvas.height();
    uint16_t colorPlanes = 1;
    uint16_t bpp = 32;
    uint32_t compressionMethod = 0;
    uint32_t imageSize = 0;
    uint32_t horizontalResolution = 0;
    uint32_t verticalResolution = 0;
    uint32_t colorPalette = 0;
    uint32_t importantColors = 0;

    writeBytes(file, fileSize);
    writeBytes(file, reserved);
    writeBytes(file, dataOffset);
    writeBytes(file, headerSize);
    writeBytes(file, width);
    writeBytes(file, height);
    writeBytes(file, colorPlanes);
    writeBytes(file, bpp);
    writeBytes(file, compressionMethod);
    writeBytes(file, imageSize);
    writeBytes(file, horizontalResolution);
    writeBytes(file, verticalResolution);
    writeBytes(file, colorPalette);
    writeBytes(file, importantColors);

    // Row order is reversed i.e row 0 is at the bottom

    // FIXME This is mirrored

    for (auto i = canvas.m_canvas.rbegin(); i != canvas.m_canvas.rend(); i++) {
        writeBytes(file, i->toRgba());
    }

    file.close();
}
