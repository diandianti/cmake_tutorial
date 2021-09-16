//TestSqrt.cpp
#include <iostream>
#include "TutorialConfig.h"

#ifdef USE_MYMATH
#       include "MathFunctions.h"
#else
#       include <cmath>
#endif //USE_MYMATH

int main(int argc, char** argv)
{
        double inputValue = std::stod(argv[1]);
#ifdef USE_MYMATH
        double sqrtValue = mysqrt(inputValue);
#else
        double sqrtValue = sqrt(inputValue);
#endif //USE_MYMATH

        std::cout << "Input value is :" << inputValue << std::endl;
        std::cout << "Sqrt value is :" << sqrtValue << std::endl;

        return 0;
}

