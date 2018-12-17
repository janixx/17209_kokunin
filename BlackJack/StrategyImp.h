#ifndef STRATEGY_IMP_H
#define STRATEGY_IMP_H
#include "strategy.h"

class StrategyImp : public Strategy {
public:
	unsigned int score = 0u;
	unsigned int number = 0u;
	void getScore(const StackCard & stack) { score = stack.score(); }
};

#endif