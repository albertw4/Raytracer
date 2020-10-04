CXXFLAGS = -g -pedantic -Wall -Wextra -std=c++17 -I. -O2
LDFLAGS = -pthread

SRCS_CPP = \
	geometry/Point.cpp \
	geometry/Vector.cpp \
	geometry/Ray.cpp \
	output/PGMOut.cpp \
	scene/Camera.cpp \
	scene/Scene.cpp \
	scene/primitive/Intersection.cpp \
	scene/primitive/Plane.cpp \
	scene/primitive/Primitive.cpp \
	scene/primitive/Sphere.cpp \
	tracer/LightModel.cpp \
	tracer/Raytracer.cpp \
	raster/ArrayRaster.cpp \
	raster/Raster.cpp \
	raster/ParallelRaster.cpp
SRCS_HPP = scene/primitive/Surface.h $(SRCS_CPP:.cpp=.h)
OBJS = main.o $(SRCS_CPP:.cpp=.o)

.PHONY: all
all: a.out

a.out: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): $(SRCS_HPP)

.PHONY: clean
clean:
	rm -f $(OBJS) a.out
