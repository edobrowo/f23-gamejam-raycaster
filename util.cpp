#include <algorithm>
#include "util.h"

float util::clamp(float x, float a, float b) {
    return std::min(std::max(x, a), b);
}

float util::rgbtof(int x) {
    return clamp(x, 0, 255) / 255;
}
