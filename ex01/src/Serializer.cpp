#include "Serializer.hpp"

#include <cstddef>

class Data;

Serializer::Serializer() {}

Serializer::Serializer(Serializer const &other)
{
	*this = other;
}

Serializer &Serializer::operator=(Serializer const &other)
{
	if (this != &other)
	{
		;
	}
	return (*this);
}

Serializer::~Serializer() {}

uintptr_t Serializer::serialize(Data *ptr)
{
	if (!ptr)
		return (0);
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* Serializer::deserialize(uintptr_t raw)
{
	if (!raw)
		return (NULL);
	return (reinterpret_cast<Data *>(raw));
}
