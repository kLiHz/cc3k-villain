#include "../output_txt.h"

void output_txt(const std::string & filename)
{
	std::ifstream inFile(filename);
	std::string line;
	while(getline(inFile, line)) std::cout << line << std::endl;
	inFile.close();
}
