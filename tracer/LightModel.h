#ifndef RAYTRACER_LIGHTMODEL_H
#define RAYTRACER_LIGHTMODEL_H

#include "Raytracer.h"
#include "geometry/Ray.h"
#include "scene/Scene.h"
#include "scene/primitive/Intersection.h"
#include <utility>

class LightModel {
    const Raytracer *raytracer_;
    const Scene *scene_;

public:
    LightModel(const Raytracer *raytracer, const Scene *scene) noexcept;

    [[nodiscard]] double brightness(Ray primary_ray, Intersection intersection) const noexcept;

private:
    [[nodiscard]] bool shadow(Intersection intersection) const noexcept;

    [[nodiscard]] static double ambient(Intersection intersection) noexcept;

    [[nodiscard]] double diffuse(Intersection intersection) const noexcept;

    [[nodiscard]] double specular(Ray primary_ray, Intersection intersection) const noexcept;

    [[nodiscard]] double reflection(Ray primary_ray, Intersection intersection) const noexcept;
};

#endif
