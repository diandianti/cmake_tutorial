#include <cstdlib>
#include <iostream>
#include <cmath>

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cout << "Usage:" << argv[0] << " number" << std::endl;
		return -1;
	}

	double inputValue = std::atof(argv[1]);
	std::cout << sqrt(inputValue) << std::endl;

	return 0;
}
