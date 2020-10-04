#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include "geometry/Point.h"

class Primitive;

struct Intersection {
    const Primitive *primitive;
    Point point;
    double distance;

    bool operator<(const Intersection &other) const noexcept;
};

#endif
