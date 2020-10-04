#ifndef PARALLEL_RASTER_H
#define PARALLEL_RASTER_H
#include "Raster.h"
#include "../tracer/Raytracer.h"
#include <queue>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;


class ParallelRaster : public Raster{
    int width, height, num_thread;
    mutex m;
public:
    queue<int> toProcess;
    std::vector<std::vector<int>> raster;
    int** outputImage;
    ParallelRaster(int w, int h, int threadNum);
    ~ParallelRaster();
    void render(Raytracer& ray);
    int getRaster_width();
    int getRaster_height();
    void processChunk(Raytracer& ray);
    int getNextRow();
};

#endif
