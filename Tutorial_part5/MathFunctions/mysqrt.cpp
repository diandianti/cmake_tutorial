#include "MathFunctions.h"
#include <iostream>
#include <cmath>

double mysqrt(double input)
{
	if (input <= 0) {
		return 0;
	}

	double result = input;

#if defined(HAVE_LOG) && defined(HAVE_EXP)
	result = exp(log(input) * 0.5);
	std::cout << "Computing sqrt of " << input << " to be " << result
		<< " using log and exp" << std::endl;
#else
	// do ten iterations
	for (int i = 0; i < 10; ++i) {
		if (result <= 0) {
			result = 0.1;
    	}
		double delta = input - (result * result);
		result = result + 0.5 * delta / result;
		std::cout << "Computing sqrt of " << input << " to be " << result << std::endl;
	}
#endif

	return result;
}


