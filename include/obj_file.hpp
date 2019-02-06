#pragma oncne.

#include "common.hpp"
#include "triangle.hpp"

// Wavefront OBJ file format reader

class ObjFile {
public:
    ObjFile();
    void readFile(const char *filename);
    std::vector<Triangle> triangles() const;

private:
    std::vector<Point> m_vertices;
    std::vector<Triangle> m_triangles;
};
