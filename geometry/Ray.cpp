#include "Ray.h"
#include <stdexcept>

using namespace std;

Ray::Ray(Point start_point, Vector direction, double weight) : weight_{weight} {
    if (direction == Vector::ZERO)
        throw invalid_argument("direction can not be Vector::ZERO");
    start_point_ = start_point;
    direction_ = direction.normalize();
}

Point Ray::start_point() const noexcept {
    return start_point_;
}

Vector Ray::direction() const noexcept {
    return direction_;
}

double Ray::weight() const noexcept {
    return weight_;
}


Point Ray::point_at_distance(double distance) const noexcept {
    return start_point_ + distance * direction_;
}
