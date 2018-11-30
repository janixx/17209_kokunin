#include "FirstStr.h"
namespace {
	Strategy * newFirstStr() {
		return new FirstStr;
	}
	bool ok = Factory <std::string, Strategy * (*)()>::getInstance()
		->regStrategy("first", (Strategy * (*)())newFirstStr);
};

Decision FirstStr::decide (const StackCard & stack) {
	get_score(stack);
	unsigned int aaa = StrategyImp::score;
	return ((aaa < 17u) ?  Decision::NEXT : Decision::STOP);
}
