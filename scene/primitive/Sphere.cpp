#include "Sphere.h"
#include <stdexcept>
#include <cmath>

using namespace std;

Sphere::Sphere(Point center, double radius, Surface surface) : Primitive{surface}, center_{center}, radius_{radius} {
    if (radius_ <= 0) {
        throw invalid_argument("radius must be positive");
    }
}

std::vector<Intersection> Sphere::intersections(const Ray &ray) const noexcept {
    vector<Intersection> intersections;

    Vector delta_r{ray.start_point() - center_};

    double b{delta_r.dot(ray.direction()) * 2};
    double c{delta_r.dot(delta_r) - radius_ * radius_};

    double discriminant{b * b - 4 * c};
    if (discriminant < 0) {
        return intersections;
    }
    discriminant = sqrt(discriminant);

    double distance{(-b + discriminant) / 2};
    if (distance <= 0) {
        return intersections;
    }

    intersections.push_back({this, ray.point_at_distance(distance), distance});

    distance = (-b - discriminant) / 2;
    if (distance > 0) {
        intersections.push_back({this, ray.point_at_distance(distance), distance});
    }

    return intersections;
}

Vector Sphere::get_normal(Point surface_point) const noexcept {
    return (surface_point - center_).normalize();
}
