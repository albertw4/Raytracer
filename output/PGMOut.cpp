#include "PGMOut.h"
#include <iostream>

using namespace std;

void PGMOut::save(Raster* raster) const noexcept {
    if(ArrayRaster* arrayRaster = dynamic_cast<ArrayRaster*>(raster))
    {
        cout << "P2\n";
        cout << arrayRaster->raster.front().size() << ' ' << arrayRaster->raster.size() << '\n';
        cout << "255\n";
        
        for (auto &row : arrayRaster->raster) {
            for (int value : row) {
                cout << value << ' ';
            }
            cout << '\n';
        }
        
    }

    if(ParallelRaster* parallelRaster = dynamic_cast<ParallelRaster*>(raster))
    {
        cout << "P2\n";
        cout << parallelRaster->getRaster_height() << ' ' << parallelRaster->getRaster_width() << '\n';
        cout << "255\n";

        for (int i = parallelRaster->getRaster_height() - 1; i >= 0 ; --i) 
        {
            for (int j = 0; j < parallelRaster->getRaster_width(); ++j)
            {
                cout << parallelRaster->outputImage[i][j] << ' ';
            }
            cout << '\n';
        }
    }

}
