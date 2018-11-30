#include "blackjack.h"
#include "game.h"
#include "factory.h"
#include "strategy.h"
#include "StrategyImp.h"

void ParametrsProcessing(GConfigs & mode, std::vector<std::string> & nms, std::vector<std::string> & par) {
	unsigned int i;
	for (i = 0u; i < par.size(); i++) {
		if (par[i] == "--mode=detailed") {
			mode.gMod = GameMode::DETAILED;
		}
		else if (par[i] == "--mode=fast") {
			mode.gMod = GameMode::FAST;
		}
		else if (par[i] == "--mode=tournament") {
			mode.gMod = GameMode::TOURNAMENT;
		}
		else if (par[i].front() == '-') {
			///
		}
		else {
			nms.push_back(par[i]);
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Bad input" << std::endl;
		return 1;
	}
	//Deck::firstInit();	


	int i;
	std::vector<std::string> parametrs(0);
	std::vector<std::string> names(0);
	GConfigs gamemode;
	for (i = 1; i < argc; i++)
		parametrs.push_back(std::string(argv[i]));

	ParametrsProcessing(gamemode, names, parametrs);
	std::vector<Strategy *> strategies;
	Deck deck;
	for (int i = 0; i < names.size(); ++i) {
		Factory<std::string, Strategy * (*)()> * f = Factory<std::string, Strategy * (*)()>::getInstance();
		Strategy * s = f->createStrategyByID(names[i]);
		if (nullptr == s) {
			std::cerr << "Unikown unit" << names[i] << std::endl;
			continue;
		}
		strategies.push_back(s);
	}
	Game game(gamemode, strategies);
	game.Play();
	return 0;
}