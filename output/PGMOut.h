#ifndef RAYTRACER_PGMOUT_H
#define RAYTRACER_PGMOUT_H

#include <vector>
#include "../raster/ArrayRaster.h"
#include "../raster/Raster.h"
#include "../raster/ParallelRaster.h"

class PGMOut {
public:
    void save(Raster* raster) const noexcept;
};

#endif
