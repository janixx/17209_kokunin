#include "strategy.h"
#ifndef STRATEGY_IMP_H
#define STRATEGY_IMP_H

class StrategyImp : public Strategy {
public:
	unsigned int score = 0u;
	void get_score(const StackCard & stack) { score = stack.score(); }
};

#endif