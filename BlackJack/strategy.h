#pragma once
#include "blackjack.h"
#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy {
public:
	Strategy() {}
	virtual Decision decide(const StackCard &) = 0;
};

#endif