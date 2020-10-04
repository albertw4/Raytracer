#include "Scene.h"
#include "primitive/Plane.h"
#include "primitive/Sphere.h"
#include <algorithm>
#include <array>
#include <iterator>
#include <fstream>
#include <functional>
#include <string_view>
#include <sstream>
#include <unordered_map>
#include <utility>

using namespace std;

namespace {
    class SceneBuilder {
        unordered_map<string_view, function<void(void)>> handlers{
                make_pair("camera", [this]() { this->camera(); }),
                make_pair("light", [this]() { this->light(); }),
                make_pair("surface", [this]() { this->surface(); }),
                make_pair("sphere", [this]() { this->sphere(); }),
                make_pair("plane", [this]() { this->plane(); })
        };

        Scene &scene_;
        Surface surface_{};
        istringstream instruction_;

    public:
        explicit SceneBuilder(Scene &scene) : scene_(scene) {}

        void instruction(const string &instruction) {
            instruction_ = istringstream{instruction};
            string type;
            instruction_ >> type;
            handlers[type]();
        }

    private:
        void camera() {
            Point position{point()};
            Point viewport_center{point()};
            double viewport_width, viewport_height;
            instruction_ >> viewport_width >> viewport_height;
            scene_.camera = {position, viewport_center, viewport_width, viewport_height};
        }

        void light() {
            scene_.light = point();
        }

        void surface() {
            instruction_ >> surface_.ambient
                         >> surface_.diffuse
                         >> surface_.specular
                         >> surface_.specular_exp
                         >> surface_.reflection;
        }

        void sphere() {
            Point position{point()};
            double radius;
            instruction_ >> radius;
            scene_.primitives.emplace_back(new Sphere{position, radius, surface_});
            surface_ = {};
        }

        void plane() {
            Point point_in_plane{point()};
            Vector normal_vector{vector()};
            scene_.primitives.emplace_back(new Plane{point_in_plane, normal_vector, surface_});
            surface_ = {};
        }

        Point point() {
            array<double, 3> coords{coordinates()};
            return {coords[0], coords[1], coords[2]};
        }

        Vector vector() {
            array<double, 3> coords{coordinates()};
            return {coords[0], coords[1], coords[2]};
        }

        array<double, 3> coordinates() {
            while (instruction_.peek() == ' ' || instruction_.peek() == '[' || instruction_.peek() == '<') {
                instruction_.ignore();
            }

            array<double, 3> coords{};
            for (double &coord : coords) {
                instruction_ >> coord;
            }

            while (instruction_.peek() == ' ' || instruction_.peek() == ']' || instruction_.peek() == '>') {
                instruction_.ignore();
            }

            return coords;
        }
    };
}

Scene::Scene(const string &filename) {
    SceneBuilder sb{*this};

    ifstream input{filename};
    string next;
    while (getline(input, next)) {
        if (!next.empty())
            sb.instruction(next);
    }
}

optional<Intersection> Scene::find_intersection(const Ray &ray) const {
    static const double minimum_intersection_distance = 1e-9;

    vector<Intersection> intersections;

    for (auto &primitive : primitives) {
        vector<Intersection> primitive_intersections{primitive->intersections(ray)};
        copy(primitive_intersections.begin(), primitive_intersections.end(), back_inserter(intersections));
    }

    intersections.erase(remove_if(intersections.begin(), intersections.end(), [](Intersection &intersection) {
        return intersection.distance < minimum_intersection_distance;
    }), intersections.end());
    auto closest_intersection = min_element(intersections.begin(), intersections.end());
    if (closest_intersection != intersections.end()) {
        return *closest_intersection;
    } else {
        return {};
    }
}


