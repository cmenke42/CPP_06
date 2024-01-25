#include <iostream>

#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::string programName = std::string(argv[0]) + " ";
		std::cout << "Usage: " << programName << "[string]\n"
		 << "Examples:" << "\n"
		 << "Char: " << programName << "\"'a'\"" << "\n"
		 << "Int: " << programName << "123" << "\n"
		 << "Float: " << programName << "1.0f" << "\n"
		 << "Double: " << programName << "1.0"
		 << std::endl;
		return (1);
	}
	ScalarConverter::convert(argv[1]);
	return (0);
}
