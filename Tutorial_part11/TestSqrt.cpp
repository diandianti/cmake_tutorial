//TestSqrt.cpp
#include <iostream>
#include "TutorialConfig.h"
#include "MathFunctions.h"

int main(int argc, char** argv)
{
        double inputValue = std::stod(argv[1]);

        double sqrtValue = mathfunctions::sqrt(inputValue);

        std::cout << "Input value is :" << inputValue << std::endl;
        std::cout << "Sqrt value is :" << sqrtValue << std::endl;

        return 0;
}

