#ifndef RAYTRACER_PRIMITIVE_H
#define RAYTRACER_PRIMITIVE_H

#include "Intersection.h"
#include "Surface.h"
#include "geometry/Ray.h"
#include <vector>

class Primitive {
public:
    Surface surface;

    explicit Primitive(Surface surface) noexcept;

    virtual ~Primitive() = default;

    [[nodiscard]] virtual std::vector<Intersection> intersections(const Ray &ray) const noexcept = 0;

    [[nodiscard]] virtual Vector get_normal(Point surface_point) const noexcept = 0;
};

#endif
