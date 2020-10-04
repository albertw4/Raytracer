#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Primitive.h"
#include <vector>

class Sphere : public Primitive {
    Point center_;
    double radius_;

public:
    Sphere(Point center, double radius, Surface surface);

    [[nodiscard]] std::vector<Intersection> intersections(const Ray &ray) const noexcept override;

    [[nodiscard]] Vector get_normal(Point surface_point) const noexcept override;
};

#endif
