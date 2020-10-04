#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Camera.h"
#include "geometry/Point.h"
#include "primitive/Primitive.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

struct Scene {
    Camera camera;
    std::optional<Point> light;
    std::vector<std::unique_ptr<Primitive>> primitives;

    explicit Scene(const std::string &filename);

    [[nodiscard]] std::optional<Intersection> find_intersection(const Ray &ray) const;
};

#endif
