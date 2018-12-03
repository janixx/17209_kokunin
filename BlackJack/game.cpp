#include "game.h"

_Game Game::_isGame = _Game::NO;

Game::Game(GConfigs & mode, std::vector<Strategy*> & str) : strategies(str), configs(mode),
		deck(mode.deckSize, mode.cMod) {
	stackcard.resize(mode.countStr);
	decisions.resize(mode.countStr);
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
	do {
		if (!bool(decisions[i])) {
			stackcard[i].push(deck.getCard());
			decisions[i] = strategies[i]->decide(stackcard[i]);
			std::cout << " " << i + 1u << " strategy: \n"
				<< "\tSummary score: " << static_cast<unsigned int>(stackcard[i].score()) << ";\n"
				<< "\tScore on turn: " << static_cast<unsigned int>(stackcard[i].top().weight) << ";\n"
				<< i + 1u << "'st " << "Strategy decision: ";
			std::cout << (!bool(decisions[i]) ? "continue the game." : "stop the game") << std::endl;
		}
		i++;
	} while (i < configs.countStr);
	for (i = 0u; i < configs.countStr; i++) {
		if (!bool(decisions[i])) {
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
				else if (stackcard[i].score() == stackcard[championNumber].score() && championNumber != i) {
					std::cout << "Drawn game! At least two strategies scored equal score!" << std::endl;
					//FIX IT! ADD FUNCTION/SMTH THAT PRINT TABLE WITH RESULTS OF GAME
					PrintResuls();
					return;
				}
			}
		}
		if (stackcard[championNumber].score() > 21u) {
			std::cout << "All strategies lost the game." << std::endl;
			//THE SAME!!!!!!!!!!!!!!!!
			PrintResuls();
			return;
		}
		std::cout << "Strategy number " << championNumber + 1u << " won the game." << std::endl;
		//ADD OUTPUT!!!!!
		PrintResuls();
		break;

	case(GameMode::TOURNAMENT):

		break;
	}

}

void Game::PrintResuls() {
	std::cout << " " << configs.countStr << " strategies competed in the game." << std::endl;
	std::cout << "\tTable with results:" << std::endl;
	std::cout << "   Number:    | Num of moves:|     Score:   " << std::endl;
	unsigned int i = 0u;
	
	for (; i < configs.countStr; i++) {
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << i + 1 <<  "|";
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << static_cast<unsigned int>(stackcard[i].size()) << "|";
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << static_cast<unsigned int>(stackcard[i].score()) << std::endl;
	}
}