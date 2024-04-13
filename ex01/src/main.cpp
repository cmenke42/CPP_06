#include <iostream>

#include "Serializer.hpp"
#include "Data.hpp"

int main(void)
{
	Data			data;
	uintptr_t	serialized;

	data.a = 42;
	data.b = 21;

	serialized = Serializer::serialize(&data);
	std::cout << "serialized: " << serialized << std::endl;
	std::cout << std::endl;

	std::cout << "original:\t" << &data
						<< "\n"
						<< "deserialize:\t"  << Serializer::deserialize(serialized)
						<< "\n== " << std::boolalpha << (&data == Serializer::deserialize(serialized))
						<< std::endl;
	std::cout << std::endl;

	std::cout << "original data.a:\t" << data.a << std::endl;
	std::cout << "deserialized data.a:\t" << Serializer::deserialize(serialized)->a << std::endl;
	std::cout << "original data.b:\t" << data.b << std::endl;
	std::cout << "deserialized data.b:\t" << Serializer::deserialize(serialized)->b << std::endl;
	return (0);
}
