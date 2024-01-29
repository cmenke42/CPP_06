#include "ScalarConverter.hpp"

#include "Parser.hpp"
#include "Output.hpp"
#include "converter.hpp"

static void processState(Parser& parser, Output& output);

void ScalarConverter::convert(std::string str)
{
	Parser parser;
	Output output;

	try
	{
		parser.parse(str, output);
		processState(parser, output);
	}
	catch (const std::exception& e)
	{
        // std::cerr << e.what() << std::endl;
        // an exception is catched if the input is invalid
        // no conversion is done
		;
	}
	output.print();
}

/**
 * @throws std::runtime_error -> If the input string cannot be converted.
 */
static void processState(Parser& parser, Output& output)
{
    switch (parser.getState())
    {
        case Parser::CHAR:
            output.setChar(parser.getValue()[0]);
            convertInitialToOtherAndSet(output.getChar(), output);
            break;
        case Parser::INT:
            convertStringAndSetFirstValue<int>(parser.getValue(), output, &Output::setInt);
            convertInitialToOtherAndSet(output.getInt(), output);
            break;
        case Parser::FLOAT:
            convertStringAndSetFirstValue<float>(parser.getValue(), output, &Output::setFloat);
            // fall through
        case Parser::PSEUDO_FLOAT:
            convertInitialToOtherAndSet(output.getFloat(), output);
            break;
        case Parser::DOUBLE:
            convertStringAndSetFirstValue<double>(parser.getValue(), output, &Output::setDouble);
            // fall through
        case Parser::PSEUDO_DOUBLE:
            convertInitialToOtherAndSet(output.getDouble(), output);
            break;
		default: break;
    }
}
