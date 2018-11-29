#include "game.h"

_Game Game::_isGame = _Game::NO;

Game::Game(GConfigs & mode, std::vector<Strategy*> & str) : strategies(str), configs(mode) {
	(mode.cMod == CardGivMode::SIMPLE) ? deck = Deck() : deck = Deck(mode.deckSize);
	stackcard.resize(mode.countStr);
	decisions.resize(mode.countStr);
}

GConfigs::GConfigs(GConfigs & other) : cMod(other.cMod), gMod(other.gMod),
		deckSize(other.deckSize), countStr(other.countStr) {}

GConfigs::GConfigs() : cMod(CardGivMode::SIMPLE), gMod(GameMode::DETAILED),
		deckSize(1u), countStr(2u) {}

GConfigs & GConfigs::operator=(const GConfigs & other) {
	if (this != &other) {
		cMod = other.cMod;
		gMod = other.gMod;
		deckSize = other.deckSize;
		countStr = other.countStr;
	}
	return *this;
}

void Game::Play() {
	startGame();
	unsigned int i = 0u;
	unsigned char c;
	while (bool(_isGame)) {
		switch (configs.gMod) {
		case (GameMode::DETAILED):
			Detailed();
			std::cin >> c;
			if (c == 27u) {
				stopGame();
				std::cout << "Game was stopped by escape pressing." << std::endl;
				return;
			} // escape pressed
			break;

		case (GameMode::FAST):
			Fast();
			break;

		case (GameMode::TOURNAMENT):
			Tournament();
			break;

		}
	}
	ResultsCalculating();
}

void Game::Detailed() {
	unsigned int i = 0u;
	for (; i < configs.countStr; i++) {
		stackcard[i].push(deck.getCard());
		strategies[i]->decide(stackcard[i]);
		std::cout << i << " strategy: \n"
			<< "Summary score: " << stackcard[i].score() << ";\n"
			<< "Score on turn: " << stackcard[i].top().weight << ";\n"
			<< i << "Strategy decision: ";
		std::cout << (bool(decisions[i]) ? "continue game." : "stop game") << std::endl;
	}
	for (i = 0u; i < configs.countStr; i++) {
		if (bool(decisions[i])) {
			std::cout << "Press any key to continue or Esc to exit" << std::endl;
			return;
		}
	}
	stopGame();
}

void Game::Tournament() {
	
}

void Game::Fast() {
	
}

void Game::ResultsCalculating() {
	unsigned int i, championNumber = 0u;
	switch (configs.gMod) {
	case(GameMode::DETAILED): case(GameMode::FAST):
		for (i = 0u; i < configs.countStr; i++) {
			if (stackcard[i].score() <= 21u) {
				if (stackcard[i].score() > stackcard[championNumber].score() || stackcard[championNumber].score() > 21u)
					championNumber = i;
				else if (stackcard[i].score() == stackcard[championNumber].score()) {
					std::cout << "Drawn game! At least two strategies scored equal score!" << std::endl;
					//FIX IT! ADD FUNCTION/SMTH THAT PRINT TABLE WITH RESULTS OF GAME
					return;
				}
			}
		}
		if (stackcard[championNumber].score() > 21u) {
			std::cout << "All strategies lost the game." << std::endl;
			//THE SAME!!!!!!!!!!!!!!!!
			return;
		}
		std::cout << "Strategy number " << championNumber << " won the game." << std::endl;
		//ADD OUTPUT!!!!!
		break;

	case(GameMode::TOURNAMENT):

		break;
	}

}