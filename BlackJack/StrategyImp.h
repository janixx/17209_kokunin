#pragma once
#include "strategy.h"
//#include "blackjack.h"

class StrategyImp : public Strategy {
public:
	unsigned int score;
	void get_score(const StackCard & stack) { score = stack.score(); }
};