#ifndef STRATEGY_H
#define STRATEGY_H

#include "blackjack.h"

class Strategy {
public:
	Strategy() {}
	virtual Decision decide(const StackCard &) = 0;
	virtual std::string getName() = 0;
	virtual std::string getID() = 0;
};

#endif