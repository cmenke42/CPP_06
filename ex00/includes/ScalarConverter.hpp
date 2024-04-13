#ifndef Scalar_Converter_HPP_INCLUDED
# define Scalar_Converter_HPP_INCLUDED

#include <string>

class ScalarConverter
{
	public:
		static void  convert(std::string str);

	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter();
};

#endif /* Scalar_Converter_HPP_INCLUDED */
