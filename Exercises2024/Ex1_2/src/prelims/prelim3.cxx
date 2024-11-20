#include <iostream>
#include <string.h>
#include <cmath>

float getNumber(std::string);

int main()
{
    float x;
    float y;
    
    x = getNumber("Enter the x component of the vector: ");
    y = getNumber("Enter the y component of the vector: ");

          
    
    

    float magnitude = sqrt(x*x + y*y);
    std::cout << "The magnitude of the vector (" << x << ", " << y << ") is " << magnitude << std::endl;
    return 0;
}

float getNumber(std::string prompt)
{
    float num;
    int valid = 0;
    std::cout << prompt;
    do {
        std::cin >> num;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
        } else {
            valid = 1;
        }
    } while (valid == 0);
    return num;
}
