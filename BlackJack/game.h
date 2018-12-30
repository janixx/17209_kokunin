#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>

#include "blackjack.h"
#include "enums.h"
#include "gui.h"
#include "StrategyImp.h"


struct GConfigs {
	CardGivMode cMod;
	GameMode gMod;
	std::string configDir;
	unsigned char deckSize;
	unsigned int countStr;

	GConfigs(GConfigs & other);
	GConfigs();
	GConfigs & operator=(const GConfigs & other);
	//void SetDirectoryPathSize(unsigned int size);
};

class Game {
	static _Game _isGame;
	std::vector<Strategy *> strategies;
	std::vector<StackCard> stackcard;
	std::vector<Decision> decisions;
	std::vector<Card> low_card;
	GConfigs configs;
	Deck deck;
	Gui * gui;
private:
	//void Detailed();
	//void Fast();
	void Tournament();
	void Turn();

	void ResultsCalculating();
	unsigned char Pair(unsigned char first, unsigned char second); //возвращает номер победителя в партии или значение
																//превышающее количество участвующих стратегий
	//void PrintResuls();
public:
	Game() = delete;

	Game(GConfigs, std::vector<Strategy *>);
	~Game() {}

	void Play(Gui * g);

	static void startGame() { _isGame = _Game::YES; }
	static void stopGame() { _isGame = _Game::NO; }

	friend class Gui;
};

#endif