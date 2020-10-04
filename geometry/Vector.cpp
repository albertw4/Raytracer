#include "Vector.h"
#include <cmath>

using namespace std;

const Vector Vector::ZERO{0, 0, 0};
const Vector Vector::X_UNIT{1, 0, 0};
const Vector Vector::Y_UNIT{0, 1, 0};

double Vector::length() const noexcept {
    return sqrt(x * x + y * y + z * z);
}

[[nodiscard]] Vector Vector::scale_to(double length) const {
    double old_length = this->length();
    double factor = length / old_length;
    return factor * *this;
}

Vector Vector::normalize() const {
    return scale_to(1);
}

double Vector::dot(Vector other) const noexcept {
    return x * other.x + y * other.y + z * other.z;
}

Vector Vector::cross(Vector other) const noexcept {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
}

Vector Vector::mirror(Vector normal) const noexcept {
    return *this - normal * (2 * this->dot(normal));
}

Vector Vector::operator+(Vector other) const noexcept {
    return {x + other.x, y + other.y, z + other.z};
}

Vector Vector::operator-(Vector other) const noexcept {
    return {x - other.x, y - other.y, z - other.z};
}

Vector Vector::operator*(double factor) const noexcept {
    return {factor * x, factor * y, factor * z};
}

Vector operator*(double factor, Vector vector) noexcept {
    return vector * factor;
}

bool Vector::operator==(Vector other) const noexcept {
    return x == other.x && y == other.y && z == other.z;
}
