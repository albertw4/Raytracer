#include "LightModel.h"
#include <cmath>

using namespace std;

LightModel::LightModel(const Raytracer *raytracer, const Scene *scene) noexcept:
        raytracer_{raytracer}, scene_{scene} {
}

double LightModel::brightness(Ray primary_ray, Intersection intersection) const noexcept {
    bool shadowed{shadow(intersection)};
    double brightness = ambient(intersection);
    if (!shadowed) {
        brightness += diffuse(intersection);
        brightness += specular(primary_ray, intersection);
        brightness += reflection(primary_ray, intersection);
    }
    return brightness;
}

bool LightModel::shadow(Intersection intersection) const noexcept {
    if (!scene_->light.has_value())
        return false;

    Vector light_vec{scene_->light.value() - intersection.point};
    Ray light_ray{intersection.point, light_vec};
    auto shadow_intersection{scene_->find_intersection(light_ray)};
    return shadow_intersection.has_value() &&
           shadow_intersection->distance < light_vec.length();
}

double LightModel::ambient(Intersection intersection) noexcept {
    return intersection.primitive->surface.ambient;
}

double LightModel::diffuse(Intersection intersection) const noexcept {
    if (!scene_->light.has_value())
        return 0.;

    double diffuse_ratio{intersection.primitive->surface.diffuse};
    if (diffuse_ratio == 0.) {
        return 0.;
    }

    Vector surface_normal{intersection.primitive->get_normal(intersection.point)};
    Vector light_vec{(scene_->light.value() - intersection.point).normalize()};
    double brightness{diffuse_ratio * surface_normal.dot(light_vec)};
    return brightness < 0 ? 0 : brightness;
}

double LightModel::specular(Ray primary_ray, Intersection intersection) const noexcept {
    if (!scene_->light.has_value())
        return 0.;

    double specular_ratio{intersection.primitive->surface.specular};
    if (specular_ratio == 0.) {
        return 0.;
    }

    Vector surface_normal{intersection.primitive->get_normal(intersection.point)};
    Vector ray_reflection{primary_ray.direction().mirror(surface_normal)};
    Vector light_vec{(scene_->light.value() - intersection.point).normalize()};
    double specular_value{ray_reflection.dot(light_vec)};

    if (specular_value < 0) {
        return 0;
    } else {
        return specular_ratio * pow(specular_value, intersection.primitive->surface.specular_exp);
    }
}

double LightModel::reflection(Ray primary_ray, Intersection intersection) const noexcept {
    double reflexion_ratio{intersection.primitive->surface.reflection};
    if (reflexion_ratio == 0.) {
        return 0.;
    }

    Vector surface_normal{intersection.primitive->get_normal(intersection.point)};
    Vector reflection_vec{primary_ray.direction().mirror(surface_normal)};
    Ray reflection_ray{intersection.point, reflection_vec,
                       primary_ray.weight() * intersection.primitive->surface.reflection};

    if (reflection_ray.weight() < 1e-9) {
        return 0;
    }

    return raytracer_->trace(reflection_ray);
}
