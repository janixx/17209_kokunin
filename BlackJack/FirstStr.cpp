#include "FirstStr.h"
namespace {
	Strategy * newSevPointStr() {
		return new FirstStr;
	}
	bool ok = Factory <std::string, Strategy * (*)()>::getInstance()
		->regStrategy("seventeen point strategy", (Strategy * (*)())newSevPointStr);
};

Decision FirstStr::decide (const StackCard & stack) {
	get_score(stack);
	return ((StrategyImp::score < 17u) ?  Decision::NEXT : Decision::STOP);
}
