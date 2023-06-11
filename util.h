#ifndef UTIL_H
#define UTIL_H

#define PI 3.14159265359
#define DR 0.0174533
#define RD 180

namespace util {

// Clamps x in [a,b]
float clamp(const float &x, const float &a, const float &b);

// Wraps x through [a,b]
float wrap(const float &x, const float &a, const float &b);

// Distance between two points
float dist(const float &px, const float &p1y, const float &p2x, const float &p2y);

// Convert an integer float component to a normalized [0,1] float
float rgbtof(const int &x);

// Wraps x through [0, 2 * PI]
float wrap2pi(const float &theta);

}

#endif // UTIL_H
