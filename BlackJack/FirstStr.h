#pragma once
#include "factory.h"
#include "StrategyImp.h"



class FirstStr : public StrategyImp {
public:
	Decision decide(const StackCard & stack) override;
	std::string getName() override;
	std::string getID() override;
	FirstStr() { score = 0u; }
};