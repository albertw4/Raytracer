#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Point.h"
#include "Vector.h"

class Ray {
    Point start_point_{};
    Vector direction_{};
    double weight_;

public:
    Ray(Point start_point, Vector direction, double weight = 1.);

    [[nodiscard]] Point start_point() const noexcept;

    [[nodiscard]] Vector direction() const noexcept;

    [[nodiscard]] double weight() const noexcept;

    [[nodiscard]] Point point_at_distance(double distance) const noexcept;
};

#endif
