#ifndef ARRAYRASTER_H
#define ARRAYRASTER_H
#include "../tracer/Raytracer.h"
#include "Raster.h"

class ArrayRaster: public Raster{

    int width, height;

public:

    ArrayRaster(int w, int h);
    
    std::vector<std::vector<int>> raster;

    void render(Raytracer& ray);
    
    int getRaster_width();

    int getRaster_height();
};

#endif