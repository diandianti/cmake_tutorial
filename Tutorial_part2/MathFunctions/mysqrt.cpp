#include "MathFunctions.h"
#include <iostream>

double mysqrt(double input)
{
	if (input <= 0) {
		return 0;
	}

	double result = input;

	// do ten iterations
	for (int i = 0; i < 10; ++i) {
		if (result <= 0) {
			result = 0.1;
    	}
		double delta = input - (result * result);
		result = result + 0.5 * delta / result;
		std::cout << "Computing sqrt of " << input << " to be " << result << std::endl;
	}

	return result;
}


