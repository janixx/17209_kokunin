#pragma once
#include "factory.h"
#include "StrategyImp.h"
#ifndef FIRST_H
#define FIRST_H
class SecondStr : public StrategyImp {
public:
	Decision decide(const StackCard & stack) override;
	SecondStr() { score = 0u; }
	~SecondStr() {}
};

#endif