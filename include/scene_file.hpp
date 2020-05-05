#pragma once

#include <map>

#include <yaml-cpp/yaml.h>

#include "camera.hpp"
#include "matrix.hpp"
#include "world.hpp"

struct Transform {
    Vector translation;
    Vector scale;

    double rotX;
    double rotY;
    double rotZ;

    Transform() : translation(Vector(0,0,0)), scale(Vector(1,1,1)), rotX(0), rotY(0), rotZ(0) {}

    Matrix toMatrix() const {
        return Matrix::translationMatrix(translation.x, translation.y, translation.z) *
            Matrix::scalingMatrix(scale.x, scale.y, scale.z) *
            Matrix::rotationMatrixX(rotX) *
            Matrix::rotationMatrixY(rotY) *
            Matrix::rotationMatrixZ(rotZ);

    }
};

class SceneFile {
public:
    SceneFile() = default;
    SceneFile(const char* filename);
    World loadFile(const char* filename);
    Canvas render();
private:
    void _loadObject(const YAML::Node &node);
    void _loadDefine(const YAML::Node &node);

    Point _decodePoint(const YAML::Node &node);
    Vector _decodeVector(const YAML::Node &node);
    Color _decodeColor(const YAML::Node &node);

    void _loadMaterial(const YAML::Node &node);
    Material _decodeMaterial(const YAML::Node &node);

    void _loadTransform(const YAML::Node &node);
    Transform _decodeTransform(const YAML::Node &node);

    Camera m_camera;
    World m_world;

    std::map<std::string, Material> m_materials;
    std::map<std::string, Transform> m_transforms;
};
