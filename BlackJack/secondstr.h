#pragma once
#include "factory.h"
#include "StrategyImp.h"
class SecondStr : public StrategyImp {
public:
	Decision decide(const StackCard & stack) override;
	SecondStr() { score = 0u; }
	~SecondStr() {}
};