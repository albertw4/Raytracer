#include "ArrayRaster.h"
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

ArrayRaster::ArrayRaster(int w, int h) 
{
    width = w;
    height = h;
}

void ArrayRaster::render(Raytracer& ray) 
{
    const Viewport vp{width, height};

    for (int y_pixel = height - 1; y_pixel >= 0; --y_pixel) {
        raster.emplace_back();

        for (int x_pixel = 0; x_pixel < width; ++x_pixel) {
            auto[x, y] = vp.convert_pixels(x_pixel, y_pixel);
            double brightness= 0.0;
            if (x >= -1 && x <= 1 && y>= -1 && y <= 1) 
            brightness = ray.trace_primary(x, y);
            raster.back().push_back(brightness);
        }
    }
}

int ArrayRaster::getRaster_width(){ return width;}

int ArrayRaster::getRaster_height(){ return height;}


