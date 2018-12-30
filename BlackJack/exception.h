#ifndef EXEPTION_H
#define EXEPTION_H
#include <exception>
#include <iostream>

class BadArguments : public std::exception {
public:
	int what() {
		std::cout << "Undefined strategy ID" << std::endl;
		return 0;
	}
};
class MemoryError : public std::exception {};
#endif