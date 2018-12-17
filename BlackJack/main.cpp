#include "blackjack.h"
#include "exception.h"
#include "factory.h"
#include "game.h"
#include "strategy.h"
#include "StrategyImp.h"

void ParametrsProcessing(GConfigs & mode, std::vector<std::string> & ID, std::vector<std::string> & par) {
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
			std::string::iterator it = par[i].begin();
			std::string tmp = "--configs";
			std::string::iterator jt = tmp.begin();
			for (; (jt < tmp.end()) && (it < par[i].end()); jt++, it++) {
				if (*jt != *it) {
					std::cout << "Undefined argument for programm!!" << par[i] << std::endl;
					throw BadArguments();
				}
			}
			it = par[i].begin() + 9;
			jt = par[i].end();
			std::copy(it, jt, mode.configDir);
		}
		else {
			ID.push_back(par[i]);
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Bad input" << std::endl;
		return 1;
	}

	std::vector<std::string> parametrs(0);
	std::vector<std::string> ID(0);
	GConfigs mode;
	for (int i = 1; i < argc; i++)
		parametrs.push_back(std::string(argv[i]));
	try {
		ParametrsProcessing(mode, ID, parametrs);
	}
	catch (BadArguments a) {
		a.what();
	}
	std::vector<Strategy *> strategies;
	for (int i = 0; i < ID.size(); ++i) {
		Factory<std::string, Strategy * (*)()> * f = Factory<std::string, Strategy * (*)()>::getInstance();
		Strategy * s = f->createStrategyByID(ID[i]);
		if (nullptr == s) {
			std::cerr << "Unikown unit" << ID[i] << std::endl;
			continue;
		}
		strategies.push_back(s);
	}

	Game game(mode, std::move(strategies));
	Gui gui(&game);
	game.Play(&gui);
	return 0;
}