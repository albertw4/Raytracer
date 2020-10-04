#include "Intersection.h"

bool Intersection::operator<(const Intersection &other) const noexcept {
    return distance < other.distance;
}
