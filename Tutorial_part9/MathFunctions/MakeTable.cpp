#include <cmath>
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
	if (argc < 2) {
		return -1;
	}

	std::ofstream tableFile(argv[1]);

	tableFile << "float sqrtTable[10] = {\n\t";

	for (int i = 1; i <= 10; i++) {
		tableFile << sqrt(i) << " ," ;
	}

	tableFile << "\n};\n";
	tableFile.close();

	return 0;
}

