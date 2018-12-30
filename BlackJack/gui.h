#ifndef GUI_H
#define GUI_H
#include <list>
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
	void StrategiesList() const;
	void TableResults(const std::vector<unsigned char> & table) const;
	//void PairResults(unsigned char first, unsigned char second) const;
	void TourneyResults(std::vector<unsigned char> results) const;
};
#endif