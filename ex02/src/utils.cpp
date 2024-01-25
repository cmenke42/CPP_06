#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

Base* generate(void)
{	
	std::srand(std::time(0));
	int i = std::rand() % 3;

	switch (i)
	{
		case 0: return new A();
		case 1: return new B();
		default: return new C();
	}
}

void identify(Base& p)
{
	try
	{
		dynamic_cast<A&>(p);
		std::cout << "Type: A" << std::endl;
		return ;
		
	}
	catch(const std::exception& e) {}

	try
	{
		dynamic_cast<B&>(p);
		std::cout << "Type: B" << std::endl;
		return ;
		
	}
	catch(const std::exception& e) {}

	try
	{
		dynamic_cast<C&>(p);
		std::cout << "Type: C" << std::endl;
		return ;
		
	}
	catch(const std::exception& e) {}

	std::cout << "Type unknown" << std::endl;
}

void identify(Base* p)
{
	identify(*p);
}
