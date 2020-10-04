#include "Plane.h"
#include <stdexcept>

using namespace std;

Plane::Plane(Point point_in_plane, Vector normal_vector, Surface surface) : Primitive{surface} {
    if (normal_vector == Vector::ZERO)
        throw invalid_argument("normal_vector must not be Vector::ZERO");
    normal_vector_ = normal_vector.normalize();
    Vector start_vector = point_in_plane - Point::ORIGIN;
    origin_distance_ = -start_vector.dot(normal_vector_);
}

vector<Intersection> Plane::intersections(const Ray &ray) const noexcept {
    double ray_plane_dot_product = normal_vector_.dot(ray.direction());

    vector<Intersection> intersections;

    if (ray_plane_dot_product != 0) {
        Vector origin_to_ray_vector = ray.start_point() - Point::ORIGIN;
        double ray_origin_plane_dot_product = normal_vector_.dot(origin_to_ray_vector);
        double distance = -(ray_origin_plane_dot_product + origin_distance_) / ray_plane_dot_product;
        if (distance > 0) {
            intersections.push_back({this, ray.point_at_distance(distance), distance});
        }
    }
    return intersections;
}

Vector Plane::get_normal(Point) const noexcept {
    return normal_vector_;
}
