#include "Parser.hpp"

#include <limits>

#include "Output.hpp"

void Parser::_handleNone(const char c)
{
	if (c == '\'')
	{
		this->_state = Parser::CHAR;
	}
	else if (c == 'i' || c == 'n')
	{
		this->_state = Parser::PSEUDO;
	}
	else if (c == '-' || c == '+' || std::isdigit(c))
	{
		this->_state = Parser::INT;
		this->_value += c;
	}
	else if (c == '.')
	{
		this->_state = Parser::DOUBLE;
		this->_value += c;
	}
	else
	{
		throw Parser::ParserException();
	}
}

void Parser::_handleChar(const char c)
{
	if (c == '\'')
		this->_end = true;
	else if (std::isprint(c))
		this->_value += c;
	else
		throw Parser::ParserException();
}

void Parser::_handleInt(const char c)
{
	if (c == '.')
	{
		this->_value += c;
		this->_state = Parser::DOUBLE;
	}
	else if (c == 'i' || c == 'n')
		this->_state = Parser::PSEUDO;
	else if (std::isdigit(c))
		this->_value += c;
	else
		throw Parser::ParserException();
}

void Parser::_handleDouble(const char c)
{
	if (c == 'f')
	{
		this->_state = Parser::FLOAT;
		this->_end = true;
	}
	else if (std::isdigit(c))
	{
		this->_value += c;
		this->_fractionalPartSize++;
	}
	else
		throw Parser::ParserException();
}

void Parser::_handlePseudoLiteral(const std::string& str, Output& output)
{
	if (str == "nan")
		output.setDouble(std::numeric_limits<double>::quiet_NaN());
	else if (str == "nanf")
		output.setFloat(std::numeric_limits<float>::quiet_NaN());
	else if (str == "inf")
		output.setDouble(std::numeric_limits<double>::infinity());
	else if (str == "inff")
		output.setFloat(std::numeric_limits<float>::infinity());
	else if (str == "-inf")
		output.setDouble(-std::numeric_limits<double>::infinity());
	else if (str == "-inff")
		output.setFloat(-std::numeric_limits<float>::infinity());
	else
		throw Parser::ParserException();
	if(output.isDoubleSet())
		this->_state = Parser::PSEUDO_DOUBLE;
	else
		this->_state = Parser::PSEUDO_FLOAT;
}
