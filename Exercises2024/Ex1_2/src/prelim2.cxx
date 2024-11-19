#include <iostream>
#include <string.h>
#include <cmath>
int main()
{
    float x = 2.3;
    float y = 4.5;

    float magnitude = sqrt(x*x + y*y);
    std::cout << "The magnitude of the vector (" << x << ", " << y << ") is " << magnitude << std::endl;
    return 0;
}