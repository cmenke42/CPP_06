#include <sstream>
#include <limits>
#include <stdexcept>

#include "Output.hpp"

/* ------------------------ Convert and Set initial value from input ------------------- */

/**
 * @brief This function converts an input string to a specified type.
 *
 * And if succesful it updates the first value of an output object with the provided setter.
 *
 * @tparam T The type to convert the input string to.
 * @param input The string to convert.
 * @param output The output object to update.
 * @param setter The member function of the Output class to use for setting the first value.
 *
 * @throws std::runtime_error -> If the input string cannot be converted.
 */
template <typename T>
void convertStringAndSetFirstValue(const std::string& input, Output& output, void (Output::*setter)(T))
{
    T value;
    std::istringstream iss(input);
    if (iss >> value && iss.eof())
        (output.*setter)(value);
    else
        throw std::runtime_error("Couldn't convert string to requested type");
}

/* ------------------------ Convert to other types -------------------------------- */

template <typename From>
void convertInitialToOtherAndSet(From value, Output& output)
{
    if (isInfinityOrNaN(value))
    {
        setOutputForPseudoLiteral(output, value);
        return ;
    }
    if (isWithinCharRange(value))
        output.setChar(static_cast<char>(value));
    if (isWithinIntRange(value))
        output.setInt(static_cast<int>(value));
    if (isWithinFloatRange(value))
        output.setFloat(static_cast<float>(value));
    if (isWithinDoubleRange(value))
        output.setDouble(static_cast<double>(value));
}

/* ------------------------ Infinity and NaN Checker ---------------------------------------- */

template <typename From>
bool isInfinityOrNaN(From value)
{
    bool isInfinity = false;
    bool isNaN = false;

    if (std::numeric_limits<From>::has_infinity)
    {
        bool isPositiveInfinity = (value == std::numeric_limits<From>::infinity());
        bool isNegativeInfinity = (value == -std::numeric_limits<From>::infinity());
        isInfinity = (isPositiveInfinity || isNegativeInfinity);
    }

    if (std::numeric_limits<From>::has_quiet_NaN)
        isNaN = (value != value);

    return (isInfinity || isNaN);
}

/* ------------------------ Output Setters ---------------------------------------- */

/**
 * @throws std::runtime_error -> Always throws, as this function is for unsupported types.
 */
template <typename T>
void setOutputForPseudoLiteral(Output& output, T value)
{
    (void)output;
    (void)value;
    throw std::runtime_error("Unsupported type");
}

// float
void setOutputForPseudoLiteral(Output& output, float value)
{
    output.setDouble(static_cast<double>(value));
}

// double
void setOutputForPseudoLiteral(Output& output, double value)
{
    output.setFloat(static_cast<float>(value));
}

/* ------------------------ Range Checkers ---------------------------------------- */
// char
template <typename From>
bool isWithinCharRange(From value)
{
    return (value >= std::numeric_limits<char>::min())
            && (value <= std::numeric_limits<char>::max());
}

/* --- For integer types --- */
template <typename From>
bool isWithinIntRange(From value)
{
    return (value >= std::numeric_limits<int>::min())
            && (value <= std::numeric_limits<int>::max());
}

bool isWithinIntRange(float value)
{
    return (value >= static_cast<float>(std::numeric_limits<int>::min())
            && value <= static_cast<float>(std::numeric_limits<int>::max()));
}

bool isWithinIntRange(double value)
{
    return (value >= static_cast<double>(std::numeric_limits<int>::min())
            && value <= static_cast<double>(std::numeric_limits<int>::max()));
}

/* --- End of integer types --- */

// float
template <typename From>
bool isWithinFloatRange(From value)
{
    return (value >= -std::numeric_limits<float>::max())
            && (value <= std::numeric_limits<float>::max());
}

// double
template <typename From>
bool isWithinDoubleRange(From value)
{
    return (value >= -std::numeric_limits<double>::max())
            && (value <= std::numeric_limits<double>::max());
}
