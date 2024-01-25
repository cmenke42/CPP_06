#include <iostream>

#include "Serializer.hpp"
#include "Data.hpp"

int main(void)
{
	Data		data;
	uintptr_t	serialized;

	data.a = 42;
	data.b = 21;
	std::cout << "data.a: " << data.a << std::endl;
	std::cout << "data.b: " << data.b << std::endl;
	serialized = Serializer::serialize(&data);
	std::cout << "serialized: " << serialized << std::endl;
	std::cout << "deserialized data.a: " << Serializer::deserialize(serialized)->a << std::endl;
	std::cout << "deserialized data.b: " << Serializer::deserialize(serialized)->b << std::endl;
	return (0);
}
