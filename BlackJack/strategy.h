#pragma once
#include "blackjack.h"

class Strategy {
public:
	Strategy() {}
	virtual Decision decide(const StackCard &) = 0;
};