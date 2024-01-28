#ifndef PARSER_HPP_INCLUDED
# define PARSER_HPP_INCLUDED

class Output;

# include <string>

# define SINGLE_QUOTE_LITERAL "'''"

class Parser
{
	public:

		class ParserException : public std::exception
		{
			public:
				ParserException();
				ParserException(const ParserException& other);
				ParserException&	operator=(const ParserException& other);
				virtual ~ParserException() throw();
				virtual const char*	what() const throw();
		};

		enum States
		{
			NONE,
			CHAR,
			INT,
			DOUBLE,
			FLOAT,
			PSEUDO,
			PSEUDO_FLOAT,
			PSEUDO_DOUBLE
		};

		Parser();
		Parser(const Parser& other);
		Parser& 			operator=(const Parser& other);
		~Parser();

		void  				parse(const std::string& str, Output& output);

		Parser::States  	getState() const;
		const std::string&	getValue() const;

	private:
		States				_state;
		std::string 		_value;
		bool				_end;
		int					_fractionalPartSize;
	
		void				_parseCharacters(const std::string& str);
		void				_parseOneChar(const char c);
		void 				_handleNone(const char c);
		void 				_handleChar(const char c);
		void 				_handleInt(const char c);
		void 				_handleDouble(const char c);
		void 				_handlePseudoLiteral(const std::string& str, Output& output);

		//helpers
		void 				_setSingleQuoteLiteral();
		void 				_setFractionSize(Output& output);
};

#endif /* PARSER_HPP_INCLUDED */