#pragma once
#include "factory.h"
#include "StrategyImp.h"



class FirstStr : public StrategyImp {
public:
	Decision decide(const StackCard & stack) override;
	FirstStr() { score = 0u; }
	~FirstStr() {}
};