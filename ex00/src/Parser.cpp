#include "Parser.hpp"

#include "Output.hpp"

/* -----------------------------  ParserException class----------------------------- */
Parser::ParserException::ParserException() {}

Parser::ParserException::ParserException(const ParserException& other)
{
	*this = other;
}

Parser::ParserException& Parser::ParserException::operator=(const ParserException& other)
{
	if (this != &other)
	{
		;
	}
	return (*this);
}

Parser::ParserException::~ParserException() throw() {}

const char* Parser::ParserException::what() const throw()
{
	return ("ParserException: wrong input");
}

/* -----------------------------  Parser class ----------------------------- */
Parser::Parser()
	  : _state(NONE),
	    _value(""),
		_end(false),
		_fractionalPartSize(0)
	    
{
}

Parser::Parser(const Parser& other)
{
	*this = other;
}

Parser& Parser::operator=(const Parser& other)
{
	if (this != &other)
	{
		this->_state = other._state;
		this->_value = other._value;
		this->_end = other._end;
		this->_fractionalPartSize = other._fractionalPartSize;
	}
	return (*this);
}

Parser::~Parser() {}

void Parser::parse(const std::string& str, Output& output)
{
	std::string::const_iterator it = str.begin();
	while (it < str.end())
	{
		_parseOneChar(*it);
		it++;
		if (this->_end && it != str.end())
			throw Parser::ParserException();
		if (this->_state == Parser::PSEUDO)
			break ;
	}
	if (this->_state == Parser::PSEUDO)
	{
		_handlePseudoLiteral(str, output);
		return ;
	}
	if (this->_fractionalPartSize > 0)
		output.setFractionalPartSize(this->_fractionalPartSize);
	else
		output.setFractionalPartSize(1);
}

void Parser::_parseOneChar(const char c)
{
	switch (this->_state)
	{
		case Parser::NONE: _handleNone(c); break;
		case Parser::CHAR: _handleChar(c); break;
		case Parser::INT: _handleInt(c); break;
		case Parser::DOUBLE: _handleDouble(c); break;
		default: throw Parser::ParserException();
	}
}

Parser::States  Parser::getState() const
{
	return (this->_state);
}

const std::string& Parser::getValue() const
{
	return (this->_value);
}
