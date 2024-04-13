#ifndef CONVERTER_HPP_INCLUDED
# define CONVERTER_HPP_INCLUDED

#include <sstream>
#include <limits>
#include <stdexcept>

#include "Output.hpp"

/* -------------------- Declarations --------------------------- */
template <typename T>
void    convertStringAndSetFirstValue(const std::string& input, Output& output, void (Output::*setter)(T));

template <typename From>
void    convertInitialToOtherAndSet(From value, Output& output);

template <typename From>
bool    isInfinityOrNaN(From value);

template <typename T>
void    setOutputForPseudoLiteral(Output& output, T value);
void    setOutputForPseudoLiteral(Output& output, float value);
void    setOutputForPseudoLiteral(Output& output, double value);

template <typename From>
bool    isWithinCharRange(From value);

template <typename From>
bool    isWithinIntRange(From value);
bool    isWithinIntRange(float value);
bool    isWithinIntRange(double value);

template <typename From>
bool    isWithinFloatRange(From value);

template <typename From>
bool    isWithinDoubleRange(From value);

#include "../src/converter.tpp"

#endif /* CONVERTER_HPP_INCLUDED */
