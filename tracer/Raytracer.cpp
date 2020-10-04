#include "Raytracer.h"
#include "LightModel.h"
#include <cmath>
#include <utility>

using namespace std;

namespace {
    class Viewport {
        double x_factor_;
        double x_shift_;
        double y_factor_;
        double y_shift_;

    public:
        Viewport(int x_resolution, int y_resolution) noexcept:
                x_factor_{x_resolution == 1 ? 1. : 2. / x_resolution},
                x_shift_{1. - 1. / x_resolution},
                y_factor_{y_resolution == 1 ? 1. : 2. / y_resolution},
                y_shift_{1 - 1. / y_resolution} {
        }

        [[nodiscard]] pair<double, double> convert_pixels(int x, int y) const noexcept {
            return {x * x_factor_ - x_shift_, y * y_factor_ - y_shift_};
        }
    };
}

std::vector<std::vector<int>> Raytracer::to_raster(int resolution) const noexcept {
    const Viewport vp{resolution, resolution};

    std::vector<std::vector<int>> raster;

    for (int y_pixel = resolution - 1; y_pixel >= 0; --y_pixel) {
        raster.emplace_back();

        for (int x_pixel = 0; x_pixel < resolution; ++x_pixel) {
            auto[x, y] = vp.convert_pixels(x_pixel, y_pixel);
            double brightness= 0.0;
            if (x >= -1 && x <= 1 && y>= -1 && y <= 1) 
            brightness = trace_primary(x, y);
            raster.back().push_back(brightness);
        }
    }

    return raster;
}

double Raytracer::trace_primary(double x, double y) const noexcept
{
    Ray ray{scene.camera.get_ray(x, y)};
    double brightness{static_cast<double>(trace(ray) * 255)};   
    return brightness;
}

double Raytracer::trace(Ray ray) const noexcept {
    const LightModel lm{this, &scene};
    auto intersection{scene.find_intersection(ray)};
    double brightness{intersection.has_value() ? lm.brightness(ray, intersection.value()) : 0.};
    brightness = brightness > 1. ? 1 : brightness;
    return brightness;
}

