#include "Point.h"

const Point Point::ORIGIN{0, 0, 0};

Point Point::operator+(Vector vector) const noexcept {
    return {x + vector.x, y + vector.y, z + vector.z};
}

Vector Point::operator-(Point other) const noexcept {
    return {x - other.x, y - other.y, z - other.z};
}

bool Point::operator==(Point other) const noexcept {
    return x == other.x && y == other.y && z == other.z;
}
