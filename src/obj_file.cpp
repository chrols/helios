#include "obj_file.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

ObjFile::ObjFile() {}

void ObjFile::readFile(const char *filename) {
    m_vertices.clear();
    m_triangles.clear();

    std::ifstream ifs(filename);
    std::string line;

    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "v") {
            Point p;
            iss >> p.x >> p.y >> p.z;
            m_vertices.push_back(p);
        } else if (cmd == "f") {
            size_t p1, p2, p3;
            iss >> p1 >> p2 >> p3;
            // FIXME Check existence?
            m_triangles.push_back(Triangle(
                m_vertices[p1 - 1], m_vertices[p2 - 1], m_vertices[p3 - 1]));
        } else {
            std::cerr << "Unrecognized line: " << cmd << std::endl;
        }
    }

    std::cerr << "Vertices: " << m_vertices.size() << std::endl;
    std::cerr << "Triangles: " << m_triangles.size() << std::endl;
}

std::vector<Triangle> ObjFile::triangles() const {
    return m_triangles;
}
