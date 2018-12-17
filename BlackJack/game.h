#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>

#include "blackjack.h"
#include "gui.h"
#include "StrategyImp.h"

class Game {
	static _Game _isGame;
	std::vector<Strategy *> strategies;
	std::vector<StackCard> stackcard;
	std::vector<Decision> decisions;
	GConfigs configs;
	Deck deck;
	Gui * gui;
private:
	void Detailed();
	void Fast();
	void Tournament();

	void ResultsCalculating();
	//void PrintResuls();
public:
	Game() = delete;

	Game(GConfigs, std::vector<Strategy *>);
	~Game() {}

	void Play(Gui * g);

	static void startGame() { _isGame = _Game::YES; }
	static void stopGame() { _isGame = _Game::NO; }

	friend void Gui::Results() const;
	friend void Gui::TourResults() const;
	friend void Gui::TurnResults(unsigned int i) const;
};

#endif