#include "gui.h"
#include "game.h"

void Gui::TurnResults(unsigned int i) const {
	std::cout << " " << (game->strategies[i]->getName()) << " strategy: \n"
		<< "\tSummary score: " << static_cast<unsigned int>(game->stackcard[i].score()) << ";\n"
		<< "\tScore on turn: " << static_cast<unsigned int>(game->stackcard[i].top().weight) << ";\n"
		<< i + 1u << "'st " << "Strategy decision: ";
	std::cout << (!bool(game->decisions[i]) ? "continue the game." : "stop the game.") << std::endl;
}

void Gui::Results() const {
	std::cout << " " << game->configs.countStr << " strategies competed in the game -- " << std::endl;
	unsigned int i = 0u;
	for (; i < game->configs.countStr; i++) {
		std::cout << " '" << game->strategies[i]->getName() << "' is a strategy number "
			<< i + 1 << ". '" << game->strategies[i]->getID() << "' is ID of this strategy." << std::endl;
	}
	std::cout << "\tTable with results:" << std::endl;
	std::cout << "   Number:    | Num of moves:|     Score:   " << std::endl;
	for (i = 0u; i < game->configs.countStr; i++) {
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << i + 1 << "|";
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << static_cast<unsigned int>(game->stackcard[i].size()) << "|";
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << static_cast<unsigned int>(game->stackcard[i].score()) << std::endl;
	}
}

void Gui::TourResults() const {
	
}

