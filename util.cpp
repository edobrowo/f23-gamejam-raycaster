#include <cmath>
#include <algorithm>
#include "util.h"

float util::clamp(const float &x, const float &a, const float &b) {
    return std::min(std::max(x, a), b);
}

float util::wrap(const float &x, const float &a, const float &b) {
    if (x < a) return x + (b - a) * (1 + static_cast<int>(a - x) / static_cast<int>(b - a));
    else if (x > b) return x - (b - a) * (1 + static_cast<int>(x - b) / static_cast<int>(b - a));
    else return x;
}

float util::dist(const float &p1x, const float &p1y, const float &p2x, const float &p2y) {
    return sqrt((p2x - p1x) * (p2x - p1x)+ (p2y - p1y) * (p2y - p1y));
}

float util::rgbtof(const int &x) {
    return clamp(x, 0, 255) / 255;
}

float util::wrap2pi(const float &theta) {
    return util::wrap(theta, 0, 2 * PI);
}
