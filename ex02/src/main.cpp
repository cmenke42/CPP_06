#include <iostream>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "utils.hpp"

int main(void)
{
	Base* base = generate();

	std::cout << "Identifying pointer: " << std::endl;
	identify(base);
	std::cout << "Identifying reference: " << std::endl;
	identify(*base);
	std::cout << "Identifying nonsense:" << std::endl;
	delete base;
	base = NULL;
	identify(*base);
	return (0);
}
