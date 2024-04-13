#ifndef SERIALIZER_HPP_INCLUDED
# define SERIALIZER_HPP_INCLUDED

class Data;

#include <stdint.h>

class Serializer
{
	public:
		static uintptr_t	serialize(Data* ptr);
		static Data*			deserialize(uintptr_t raw);

	private:
		Serializer();
		Serializer(const Serializer& other);
		Serializer& operator=(const Serializer& other);
		~Serializer();
};

#endif /* SERIALIZER_HPP_INCLUDED */
