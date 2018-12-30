#include "game.h"
#include "gui.h"

_Game Game::_isGame = _Game::NO;

GConfigs::GConfigs(GConfigs & other) : cMod(other.cMod), gMod(other.gMod),
configDir(other.configDir), deckSize(other.deckSize), countStr(other.countStr) {}

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

//void GConfigs::SetDirectoryPathSize(unsigned int size) {
//	configDir.resize(size);
//}

Game::Game(GConfigs mode, std::vector<Strategy*> str) : strategies(str),
		configs(mode), deck(mode.deckSize, mode.cMod), gui(nullptr) {
	
	stackcard.resize(mode.countStr);
	decisions.resize(mode.countStr);
	low_card.resize(mode.countStr);
}

void Game::Play(Gui * g) {
	startGame();
	unsigned int i = 0u;
	gui = g;
	switch (configs.gMod) {
	case (GameMode::DETAILED): case (GameMode::FAST) :
		unsigned char c;
		for (i = 0u; i < configs.countStr; i++) {
			stackcard[i].push(deck.getCard());
			low_card[i] = stackcard[i].low();
		}
		for (i = 0u; i < configs.countStr; i++) {
			strategies[i]->init(configs.configDir);
			decisions[i] = strategies[i]->decide(stackcard[i], low_card, decisions);

			if (configs.gMod == GameMode::DETAILED)
				gui->TurnResults(i);
		}
		while (bool(_isGame)) {
			Turn();
			if (configs.gMod == GameMode::DETAILED){
				c = std::getchar();
				if (c == unsigned char(27)) {
					stopGame();
					std::cout << "Game was stopped by escape pressing." << std::endl;
					return;
				} // escape pressed
			}
		}
		ResultsCalculating();
		break;

	//case (GameMode::FAST):
	//		for (i = 0u; i < configs.countStr; i++) {
	//			stackcard[i].push(deck.getCard());
	//			if (min_low.weight < stackcard[i].low().weight)
	//				min_low = stackcard[i].low();
	//			if (max_low.weight > stackcard[i].low().weight)
	//				max_low = stackcard[i].low();
	//		}
	//		for (i = 0u; i < configs.countStr; i++) {
	//			decisions[i] = strategies[i]->decide(stackcard[i], min_low, max_low);
	//		}
	//		while (bool(_isGame)) {
	//			Fast();
	//		}
	//		ResultsCalculating();
	//		break;

	case (GameMode::TOURNAMENT):
		Tournament();
		break;

	}
}

//void Game::Detailed() {
//	unsigned int i = 0u, j = 0u;
//	do {
//		if (decisions[i] == Decision::NEXT) {
//			stackcard[i].push(deck.getCard());
//			decisions[i] = strategies[i]->decide(stackcard[i], min_low, max_low);
//			gui->TurnResults(i);
//		}
//		
//		i++;
//	} while (i < configs.countStr);
//	for (j = 0u; j < configs.countStr; j++) {
//		if (decisions[j] == Decision::NEXT) {
//			std::cout << "Press any key to continue or Esc to exit" << std::endl;
//			return;
//		}
//	}
//	
//}

void Game::Turn() {
	unsigned int i = 0u;
	for(i = 0u; i < configs.countStr; i++){
		if (decisions[i] == Decision::NEXT) {
			stackcard[i].push(deck.getCard());
			decisions[i] = strategies[i]->decide(stackcard[i], low_card, decisions);
			if (configs.gMod == GameMode::DETAILED)
				gui->TurnResults(i);
		}
	} 
	for (i = 0u; i < configs.countStr; i++) {
		if (decisions[i] == Decision::NEXT) {
			if (configs.gMod == GameMode::DETAILED)
				std::cout << "Press any key to continue or Esc to exit" << std::endl;

			return;
		}
	}

	stopGame();
}

//void Game::Fast() {
//	unsigned int i = 0u, j = 0u;
//	do {
//		if (decisions[i] == Decision::NEXT) {
//			stackcard[i].push(deck.getCard());
//			decisions[i] = strategies[i]->decide(stackcard[i]);
//		}
//		i++;
//	} while (i < configs.countStr);
//
//	for (j = 0u; j < configs.countStr; j++) {
//		if (decisions[j] == Decision::NEXT)
//			return;
//	}
//
//	stopGame();
//}

void Game::Tournament() {
	unsigned char i = 0u, j = 0u, tmp = 0u;
	for (i = 0u; i < configs.countStr; i++)
		strategies[i]->init(configs.configDir);

	gui->StrategiesList();
	std::vector<unsigned char> matrix(configs.countStr * configs.countStr);
	std::vector<unsigned char> results(configs.countStr);
	for (i = 0u; i < configs.countStr - 1u; i++) {
		for (j = i + 1u; j < configs.countStr; j++) {
			tmp = Pair(i, j);
			matrix[i*configs.countStr + j] = matrix[j*configs.countStr + i] = tmp;
			results[tmp]++;
		}
	}

	gui->TableResults(matrix);
	gui->TourneyResults(results);
	stopGame();
}

unsigned char Game::Pair(unsigned char i, unsigned char j) {
	decisions[i] = decisions[j] = Decision::NEXT;
	stackcard[i].push(deck.getCard());
	stackcard[j].push(deck.getCard());
	low_card[i] = stackcard[i].low();
	low_card[j] = stackcard[j].low();
	decisions[j] = strategies[j]->decide(stackcard[j], low_card, decisions);
	decisions[j] = strategies[j]->decide(stackcard[j], low_card, decisions);
	while (decisions[i] != Decision::STOP || decisions[j] != Decision::STOP) {
		if (decisions[i] == Decision::NEXT) {
			stackcard[i].push(deck.getCard());
			decisions[i] = strategies[i]->decide(stackcard[i], low_card, decisions);
		}
		if (decisions[j] == Decision::NEXT) {
			stackcard[j].push(deck.getCard());
			decisions[j] = strategies[j]->decide(stackcard[j], low_card, decisions);
		}
	} 
	
	unsigned int ret = 0u;
	if (stackcard[i].score() <= 21u) {
		if (stackcard[i].score() > stackcard[j].score() || stackcard[j].score() > 21u)
			ret = i;
		else if (stackcard[i].score() == stackcard[j].score()) {
			ret = configs.countStr;
		}
	}
	else {
		ret = ((stackcard[j].score() <= 21u) ? j : configs.countStr);
	}
	
	stackcard[i].clear();
	stackcard[j].clear();
	deck.shufle();
	return ret;
}

void Game::ResultsCalculating() {
	unsigned int i, championNumber = 0u;
	for (i = 0u; i < configs.countStr; i++) {
		if (stackcard[i].score() <= 21u) {
			if (stackcard[i].score() > stackcard[championNumber].score() || stackcard[championNumber].score() > 21u)
				championNumber = i;
			else if (stackcard[i].score() == stackcard[championNumber].score() && championNumber != i) {
				std::cout << "Drawn game! At least two strategies scored equal score!" << std::endl;
				gui->Results();
				return;
			}
		}
	}
	if (stackcard[championNumber].score() > 21u) {
		std::cout << "All strategies lost the game." << std::endl;
		gui->Results();
		return;
	}
	std::cout << "Strategy number " << championNumber + 1u << " won the game." << std::endl;
	gui->Results();
}

//void Game::PrintResuls() {
//	std::cout << " " << configs.countStr << " strategies competed in the game." << std::endl;
//	std::cout << "\tTable with results:" << std::endl;
//	std::cout << "   Number:    | Num of moves:|     Score:   " << std::endl;
//	unsigned int i = 0u;
//	
//	for (; i < configs.countStr; i++) {
//		std::cout.width(13);
//		std::cout.setf(std::ios::left);
//		std::cout << "    " << i + 1 <<  "|";
//		std::cout.width(13);
//		std::cout.setf(std::ios::left);
//		std::cout << "    " << static_cast<unsigned int>(stackcard[i].size()) << "|";
//		std::cout.width(13);
//		std::cout.setf(std::ios::left);
//		std::cout << "    " << static_cast<unsigned int>(stackcard[i].score()) << std::endl;
//	}
//}