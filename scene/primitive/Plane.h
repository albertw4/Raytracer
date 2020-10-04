#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Primitive.h"

class Plane : public Primitive {
    Vector normal_vector_{};
    double origin_distance_{};

public:
    Plane(Point point_in_plane, Vector normal_vector, Surface surface);

    [[nodiscard]] std::vector<Intersection> intersections(const Ray &ray) const noexcept override;
    [[nodiscard]] Vector get_normal(Point surface_point) const noexcept override;

};

#endif
