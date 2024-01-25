#ifndef SERIALIZER_HPP_INCLUDED
# define SERIALIZER_HPP_INCLUDED

class Data;

#include <stdint.h>

class Serializer
{
	public:
		static uintptr_t	serialize(Data* ptr);
		static Data*		deserialize(uintptr_t raw);

	private:
		Serializer();
		Serializer(Serializer const &other);
		Serializer&			operator=(Serializer const &other);
		~Serializer();
};

#endif /* SERIALIZER_HPP_INCLUDED */
