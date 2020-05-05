#include "scene_file.hpp"

#include <cmath>

#include <yaml-cpp/yaml.h>

#include "material.hpp"
#include "camera.hpp"
#include "plane.hpp"
#include "cube.hpp"
#include "light.hpp"

SceneFile::SceneFile(const char* filename) {
    loadFile(filename);
}


World SceneFile::loadFile(const char* filename) {
    YAML::Node config = YAML::LoadFile(filename);

    m_materials.clear();

    if (config.Type() != YAML::NodeType::Sequence) {
        throw std::runtime_error("Invalid file format");
    }

    for (auto node : config) {
        if (node.Type() != YAML::NodeType::Map) {
            throw std::runtime_error("Invalid file format");
        }

        if (node["add"]) {
            _loadObject(node);
        } else if (node["define"]) {
            _loadDefine(node);
        }
    }

    std::cout << filename << " loaded\n";
    return m_world;
}

Canvas SceneFile::render() {
    return m_camera.render(m_world);
}

void SceneFile::_loadObject(const YAML::Node &node) {
    std::string type = node["add"].as<std::string>();

    if (type == "camera") {
        double width = node["width"].as<double>();
        double height = node["height"].as<double>();
        double fov = (M_PI / 180.0) * node["field-of-view"].as<double>();
        Point from = _decodePoint(node["from"]);
        Point to = _decodePoint(node["to"]);
        Vector up = _decodeVector(node["up"]);
        m_camera = Camera(width, height, fov);
        m_camera.setTransform(Matrix::viewTransform(from, to, up));
        return;
    } else if (type == "light") {
        Color i = _decodeColor(node["intensity"]);
        Point p = _decodePoint(node["at"]);
        PointLight l(p, i);
        m_world.addLight(l);
        return;
    }

    std::shared_ptr<Object> o;

    if (type == "plane") {
        o = std::make_shared<Plane>();
    } else if (type == "sphere") {
        o = std::make_shared<Sphere>();
    } else if (type == "cube") {
        o = std::make_shared<Cube>();
    } else {
        throw std::runtime_error("Invalid file format: unhandled object");
    }

    Transform t = _decodeTransform(node["transform"]);
    Matrix mt = t.toMatrix();

    Material m;
    if (node["material"]) {
        if (node["material"].IsScalar()) {
            m = m_materials[node["material"].as<std::string>()];
        } else {
            m = _decodeMaterial(node["material"]);
        }
    }

    o->setTransform(t.toMatrix());
    o->material = m;

    m_world.addObject(o);
}


void SceneFile::_loadDefine(const YAML::Node &node) {
    auto value = node["value"];

    if (!value) {
        throw std::runtime_error("Invalid file format: missing value");
    }

    switch (value.Type()) {
    case YAML::NodeType::Map:
        _loadMaterial(node);
        break;
    case YAML::NodeType::Sequence:
        _loadTransform(node);
        break;
    default:
        throw std::runtime_error("Invalid file format: wrong value");
    }
}

Point SceneFile::_decodePoint(const YAML::Node &value) {
    double x = value[0].as<double>();
    double y = value[1].as<double>();
    double z = value[2].as<double>();
    return Point(x, y, z);
}

Vector SceneFile::_decodeVector(const YAML::Node &value) {
    double x = value[0].as<double>();
    double y = value[1].as<double>();
    double z = value[2].as<double>();
    return Vector(x, y, z);
}

Color SceneFile::_decodeColor(const YAML::Node &value) {
    if (value.size() != 3) {
        throw std::runtime_error("Invalid file format: wrong color format");
    }

    auto r = value[0].as<double>();
    auto g = value[1].as<double>();
    auto b = value[2].as<double>();

    return Color(r, g, b);
}

void SceneFile::_loadMaterial(const YAML::Node &node) {
    std::string name = node["define"].as<std::string>();

    if (node["extend"]) {
        std::string parent = node["extend"].as<std::string>();
        m_materials[name] = m_materials[parent];
    }

    m_materials[name] = _decodeMaterial(node["value"]);
}

Material SceneFile::_decodeMaterial(const YAML::Node &value) {
    Material m;

    if (value["color"]) {
        m.color = _decodeColor(value["color"]);
    }

    if (value["pattern"]) {
        std::string type = value["pattern"][0].as<std::string>();
        auto c1 = _decodeColor(value["pattern"][1]);
        auto c2 = _decodeColor(value["pattern"][2]);

        if (type == "stripe") {
            m.pattern = new StripePattern(c1, c2);
        } else if (type == "gradient") {
            m.pattern = new GradientPattern(c1, c2);
        } else if (type == "ring") {
            m.pattern = new RingPattern(c1, c2);
        } else if (type == "checkers") {
            m.pattern = new CheckersPattern(c1, c2);
        }
    }

    m.ambient = value["ambient"].as<double>(m.ambient);
    m.diffuse = value["diffuse"].as<double>(m.diffuse);
    m.specular = value["specular"].as<double>(m.specular);
    m.shininess = value["shininess"].as<double>(m.shininess);
    m.reflective = value["reflective"].as<double>(m.reflective);
    m.transparency = value["transparency"].as<double>(m.transparency);
    m.refraction = value["refraction"].as<double>(m.refraction);

    return m;
}

void SceneFile::_loadTransform(const YAML::Node &node) {
    std::string name = node["define"].as<std::string>();
    m_transforms[name] =  _decodeTransform(node["value"]);
}

Transform SceneFile::_decodeTransform(const YAML::Node &value) {
    Transform t;

    for (auto e : value) {
        if (e.Type() == YAML::NodeType::Scalar) {
            std::string parent = e.as<std::string>();
            t = m_transforms[parent];
        }
    }

    for (auto e : value) {
        if (e.Type() == YAML::NodeType::Sequence) {
            std::string type = e[0].as<std::string>();
            double x = e[1].as<double>();

            if (type == "rotate-x") {
                t.rotX = x;
                continue;
            } else if (type == "rotate-y") {
                t.rotY = x;
                continue;
            } else if (type == "rotate-z") {
                t.rotZ = x;
                continue;
            }


            double y = e[2].as<double>();
            double z = e[3].as<double>();

            if (type == "translate") {
                t.translation = Vector(x, y, z);
            } else if (type == "scale") {
                t.scale = Vector(x, y, z);
            } else {
                throw std::runtime_error("Invalid file format: unknown transform type");
            }
        }
    }

    return t;
}
