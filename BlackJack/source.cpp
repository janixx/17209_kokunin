#include "blackjack.h"
#include "game.h"
#include "factory.h"
#include "strategy.h"

int main(int argc, char *argv[]) {
	//std::cout << "Write count of card's decks: ";
	//unsigned int n;
	//std::cin >> n;
	//std::cout << "\n";
	//Deck a = Deck((unsigned char)n);
	//a.PrintParam();

	std::vector<Strategy *> strategies;
	for (int i = 1; i < argc; ++i) {
		Factory<std::string, Strategy * (*)()> * f = Factory<std::string, Strategy * (*)()>::getInstance();
		Strategy * s = f->createStrategyByID(argv[i]);
		if (nullptr == s) {
			std::cerr << "Unikown unit" << argv[i] << std::endl;
			continue;
		}
		strategies.push_back(s);
	}

	return 0;
}