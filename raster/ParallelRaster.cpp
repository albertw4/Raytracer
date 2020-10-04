#include "ParallelRaster.h"
#include <iostream>

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

ParallelRaster::ParallelRaster(int w, int h, int threadNum)
{
    width = w;
    height = h;
    num_thread = threadNum;

    for (int i = 0; i < height; ++i)
    {
        toProcess.push(i);
    }

    outputImage = new int* [height];
    for (int i = 0; i < height; ++i) {
        outputImage[i] = new int[width];
        for (int j = 0; j < width; ++j)
        {
            outputImage[i][j] = 0;
        }
    }
}

ParallelRaster::~ParallelRaster()
{
    for (int i = 0; i < height; ++i) {
        delete [] outputImage[i];
    }
    delete[] outputImage;
}

int ParallelRaster::getNextRow()
{
    lock_guard<mutex> lock(m);
    if (!toProcess.empty())
    {
        int row = toProcess.front();
        toProcess.pop();
        return row;
    }
    else
    {
        return -1;
    }
}

void ParallelRaster::processChunk(Raytracer& ray)
{
    const Viewport vp{width, height};

    while(true)
    {
        int row = getNextRow();

        if (row == -1)
        {
            break;
        }

        //cout << "Thread " << "is processing row at " << row << endl;

        int y_pixel = row;
        for (int x_pixel = 0; x_pixel < width; ++x_pixel) 
        {
            auto[x, y] = vp.convert_pixels(x_pixel, y_pixel);
            double brightness= 0.0;
            if (x >= -1 && x <= 1 && y>= -1 && y <= 1) 
            brightness = ray.trace_primary(x, y);
            outputImage[row][x_pixel] = brightness;
        }
    }
}


void ParallelRaster::render(Raytracer& ray) 
{
    vector<thread> threads;
    for (int i = 0; i < 4; ++i)
    {
        threads.emplace_back(&ParallelRaster::processChunk, this, ref(ray));
    }

    for (int i = 0; i < 4; ++i)
    {
        threads[i].join();
    }
}

int ParallelRaster::getRaster_width(){ return width;}

int ParallelRaster::getRaster_height(){ return height;}

