#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "geometry/Point.h"
#include "geometry/Ray.h"
#include "geometry/Vector.h"

class Camera {
    Point position_{};
    Vector view_vector_{0, 0, -1};
    Vector right_vector_{Vector::X_UNIT};
    Vector up_vector_{Vector::Y_UNIT};

public:
    Camera() = default;

    Camera(Point position, Point viewport_center, double viewport_width, double viewport_height);

    [[nodiscard]] Ray get_ray(double viewport_horizontal, double viewport_vertical) const;
};


#endif
