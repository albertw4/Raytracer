#ifndef RAYTRACER_POINT_H
#define RAYTRACER_POINT_H

#include "Vector.h"

struct Point {
    static const Point ORIGIN;

    double x;
    double y;
    double z;

    Point operator+(Vector vector) const noexcept;

    Vector operator-(Point other) const noexcept;

    bool operator==(Point other) const noexcept;
};

#endif
