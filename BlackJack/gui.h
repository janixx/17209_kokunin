#ifndef GUI_H
#define GUI_H
#include <string>
#include "blackjack.h"
#include "strategy.h"

class Game;
class Gui {
	Game * game;
	Gui() = delete;
public:
	Gui(Game * other) : game(other) {}

	void TurnResults(unsigned int i) const;
	void Results() const;
	void TourResults() const;
};
#endif