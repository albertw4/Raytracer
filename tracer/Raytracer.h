#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include "scene/Scene.h"
#include <vector>

struct Raytracer {
    Scene scene;

    [[nodiscard]] std::vector<std::vector<int>> to_raster(int resolution) const noexcept;

    [[nodiscard]] double trace(Ray ray) const noexcept;

    [[nodiscard]] double trace_primary(double x, double y) const noexcept;
};

#endif
