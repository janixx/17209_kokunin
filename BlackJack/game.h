#include "StrategyImp.h"
enum class _Game : unsigned char {
	YES = 0xFF,
	NO = 0x00
};

enum class CardGivMode : unsigned char {
	SIMPLE = 0xFF,
	DEFAULT = 0x00
};

enum class GameMode : unsigned char {
	DETAILED,
	NOT_DETAILED,
	TOURNAMENT
};

struct GConfigs {
	CardGivMode cMod;
	GameMode gMod;
};

class Game {
	static _Game _isGame;
	std::vector<Strategy *> & strategies;
	Deck deck;
public:
	static void startGame() { _isGame = _Game::YES; }
	static void stopGame() { _isGame = _Game::NO; }
	Game(unsigned int, GConfigs, std::vector<Strategy *> &);
	~Game();
};