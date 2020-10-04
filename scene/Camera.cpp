#include "Camera.h"
#include <stdexcept>

using namespace std;

Camera::Camera(Point position, Point viewport_center, double viewport_width, double viewport_height) : position_{
        position} {
    if (position == viewport_center)
        throw invalid_argument("position can not be the same as viewport_center");
    if (viewport_width <= 0)
        throw invalid_argument("viewport_width must be positive");
    if (viewport_height <= 0)
        throw invalid_argument("viewport_width must be positive");

    view_vector_ = viewport_center - position;
    if (view_vector_.normalize() == Vector::Y_UNIT)
        throw invalid_argument("position and viewport_center can not look straight up or down");

    right_vector_ = view_vector_.cross(Vector::Y_UNIT).scale_to(viewport_width / 2);
    up_vector_ = right_vector_.cross(view_vector_).scale_to(viewport_height / 2);
}

Ray Camera::get_ray(double viewport_horizontal, double viewport_vertical) const {
    Vector horizontal = right_vector_ * viewport_horizontal;
    Vector vertical = up_vector_ * viewport_vertical;
    Vector direction = view_vector_ + horizontal + vertical;
    return {position_, direction};
}
