#pragma once
#include "factory.h"
#include "StrategyImp.h"
class SecondStr : public StrategyImp {
public:
	Decision decide(const StackCard & stack) override;
	std::string getName() override;
	std::string getID() override;
	SecondStr() { score = 0u; }
	~SecondStr() {}
};