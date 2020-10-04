#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H

struct Vector {
    static const Vector ZERO;
    static const Vector X_UNIT;
    static const Vector Y_UNIT;

    double x;
    double y;
    double z;

    [[nodiscard]] double length() const noexcept;

    [[nodiscard]] Vector scale_to(double length) const;

    [[nodiscard]] Vector normalize() const;

    [[nodiscard]] double dot(Vector other) const noexcept;

    [[nodiscard]] Vector cross(Vector other) const noexcept;

    [[nodiscard]] Vector mirror(Vector normal) const noexcept;

    Vector operator+(Vector other) const noexcept;

    Vector operator-(Vector other) const noexcept;

    Vector operator*(double factor) const noexcept;

    bool operator==(Vector other) const noexcept;
};

Vector operator*(double factor, Vector vector) noexcept;

#endif
