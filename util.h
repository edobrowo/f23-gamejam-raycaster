#ifndef UTIL
#define UTIL

namespace util {

// Clamps x in [a,b]
float clamp(float x, float a, float b);

// Convert an integer float component to a normalized [0,1] float
float rgbtof(int x);


}

#endif // UTIL
