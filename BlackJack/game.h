#include "StrategyImp.h"
#include "blackjack.h"

#ifndef GAME_H

#define GAME_H 1

class Game {
	static _Game _isGame;
	std::vector<Strategy *> & strategies;
	std::vector<StackCard> stackcard;
	std::vector<Decision> decisions;
	GConfigs & configs;
	Deck deck;
private:
	void Detailed();
	void Fast();
	void Tournament();
	void ResultsCalculating();
	void PrintResuls();
public:
	static void startGame() { _isGame = _Game::YES; }
	static void stopGame() { _isGame = _Game::NO; }
	Game() = delete;
	Game(GConfigs &, std::vector<Strategy *> &);
	~Game() {}
	void Play();
};

#endif