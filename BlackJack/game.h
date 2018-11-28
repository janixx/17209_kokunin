#include "StrategyImp.h"
enum class _Game : unsigned char {
	YES = 0xFF,
	NO = 0x00
};

enum class Parametr : unsigned char {
	ONE,
	TWO,
	THREE
};

class Game {
	static _Game _isGame;
	std::vector<Strategy *> & strategies;
	Deck deck;
public:
	static void startGame() { _isGame = _Game::YES; }
	static void stopGame() { _isGame = _Game::NO; }
	Game(unsigned int, Parametr, std::vector<Strategy *> &);
};