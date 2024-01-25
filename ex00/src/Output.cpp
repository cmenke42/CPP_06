#include "Output.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

Output::Output()
      : _valueSet(false),
	    _charSet(false),
	    _intSet(false),
	    _fractionalPartSize(0),
	    _floatSet(false),
	    _doubleSet(false)
{
}

Output::Output(const Output& other)
{
	*this = other;
}

Output& Output::operator=(const Output& other)
{
	if (this != &other)
	{
		this->_valueSet = other._valueSet;
		this->_char = other._char;
		this->_charSet = other._charSet;
		this->_int = other._int;
		this->_intSet = other._intSet;
		this->_fractionalPartSize = other._fractionalPartSize;
		this->_float = other._float;
		this->_floatSet = other._floatSet;
		this->_double = other._double;
		this->_doubleSet = other._doubleSet;
	}
	return (*this);
}

Output::~Output() {}

void Output::setChar(char c)
{
	this->_char = c;
	this->_charSet = true;
	this->_valueSet = true;
}

void Output::setInt(int i)
{
	this->_int = i;
	this->_intSet = true;
	this->_valueSet = true;
}

void Output::setFloat(float f)
{
	this->_float = f;
	this->_floatSet = true;
	this->_valueSet = true;
}

void Output::setDouble(double d)
{
	this->_double = d;
	this->_doubleSet = true;
	this->_valueSet = true;
}

void Output::setFractionalPartSize(int size)
{
	this->_fractionalPartSize = size;
}

char Output::getChar() const
{
	return (this->_char);
}

int Output::getInt() const
{
	return (this->_int);
}

float Output::getFloat() const
{
	return (this->_float);
}

double Output::getDouble() const
{
	return (this->_double);
}

bool Output::isDoubleSet() const
{
	return (this->_doubleSet);
}

void Output::print() const
{
	this->printChar();
	this->printInt();
	this->printFloat();
	this->printDouble();
}

void Output::printChar() const
{
	if (this->_charSet)
	{
		if (std::isprint(this->_char))
			std::cout << "char: '" << this->_char << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
	}
	else
		std::cout << "char: impossible" << std::endl;
}

void Output::printInt() const
{
	if (this->_intSet)
		std::cout << "int: " << this->_int << std::endl;
	else
		std::cout << "int: impossible" << std::endl;
}

void Output::printFloat() const
{
	if (this->_floatSet)
	{
		std::stringstream ss;
		ss << "float: " << std::fixed << std::setprecision(this->_fractionalPartSize) << this->_float << "f";
		std::cout << ss.str() << std::endl;
	}
	else
		std::cout << "float: impossible" << std::endl;
}

void Output::printDouble() const
{
	if (this->_doubleSet)
	{
		std::stringstream ss;
		ss << "double: " << std::fixed << std::setprecision(this->_fractionalPartSize) << this->_double;
		std::cout << ss.str() << std::endl;
	}
	else
		std::cout << "double: impossible" << std::endl;
}
