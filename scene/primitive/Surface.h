#ifndef RAYTRACER_SURFACE_H
#define RAYTRACER_SURFACE_H

struct Surface {
    double ambient{0.05};
    double diffuse{0.95};
    double specular{0};
    double specular_exp{30};
    double reflection{0};
};

#endif
