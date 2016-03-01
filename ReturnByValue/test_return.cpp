// This file shows how the move constructor of a class is called when it is returned by a function.
// Returning an object from a function does not create a new instance of the object.
// Instead, it is MOVED (of course it there was a move constructor).
//
// If a function needs to return just one object and the class of the object has a move constructor, then
// just return the object instead of accessing it as a reference.

#include <iostream>

class Hello
{
public:
	Hello(void) { std::clog << "Default ctor" << std::endl; }
	Hello(const Hello& src) : value(src.value) { std::clog << "Copy ctor" << std::endl; }
	Hello(Hello &&src) : value(src.value) { std::clog << "Move ctor" << std::endl; }
	Hello &operator=(const Hello &other) { this->value = other.value; std::clog << "Copy assignment" << std::endl; return *this; }
	Hello &operator=(Hello &&other) { this->value = other.value; std::clog << "Move assignment" << std::endl; return *this; }

	int value = 0;
};

Hello test_return_by_value(void)
{
	Hello hello;	// Calls default ctor.
	hello.value = 99;

	// NOTE: The next line does NOT create a new instance. Instead, it MOVES.
	return hello;
}

void test_access_by_reference(Hello &hello)
{
	hello.value = 99;
}

int main(void)
{
	// hello_returned is created by a move ctor.
	Hello hello_returned = test_return_by_value();

	Hello hello_referenced;	// The data value is meaningless now.
	test_access_by_reference(hello_referenced);
}