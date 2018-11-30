#include "secondstr.h"
namespace {
	Strategy * newSecondStr() {
		return new SecondStr;
	}
	bool ok = Factory <std::string, Strategy * (*)()>::getInstance()
		->regStrategy("second", (Strategy * (*)())newSecondStr);
};

Decision SecondStr::decide(const StackCard & stack) {
	get_score(stack);
	return ((StrategyImp::score < 16u && StrategyImp::score > 2u) ? Decision::NEXT : Decision::STOP);
}
