#include "ScalarConverter.hpp"

#include <iostream>



// #include <limits>
// #include <iomanip>
// printConversions()
// {
// 	std::cout << "Float: " << std::endl;
// 	std::cout <<  std::fixed << std::setprecision(23) << (float)std::numeric_limits<int>::max() << std::endl;
// 	std::cout <<  std::fixed << std::setprecision(23) << (float)std::numeric_limits<int>::min() << std::endl;


// 	std::cout << "Double: " << std::endl;
// 	std::cout <<  std::fixed << std::setprecision(23) << (double)std::numeric_limits<int>::max() << std::endl;
// 	std::cout <<  std::fixed << std::setprecision(23) << (double)std::numeric_limits<int>::min() << std::endl;
// std::cout << "Double max: " << std::endl;
// std::cout << std::fixed << std::setprecision(750) 
//               << std::numeric_limits<double>::max() << std::endl;
// }



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
	// printConversions();

	// ScalarConverter converter;

	return (0);
}
