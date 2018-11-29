#include "StrategyImp.h"
enum class _Game : bool {
	YES = 0x1,
	NO = 0x0
};

enum class CardGivMode : unsigned char {
	SIMPLE = 0xFF,
	DEFAULT = 0x00
};

enum class GameMode : unsigned char {
	DETAILED = 0x00,
	FAST = 0x01,
	TOURNAMENT = 0x02
};

struct GConfigs {
	CardGivMode cMod;
	GameMode gMod;
	unsigned char deckSize;
	unsigned int countStr;
	GConfigs(GConfigs & other);
	GConfigs();
	GConfigs & operator=(const GConfigs & other);
};

class Game {
	static _Game _isGame;
	std::vector<Strategy *> & strategies;
	std::vector<StackCard> stackcard;
	std::vector<Decision> decisions;
	GConfigs & configs;
	Deck deck;
public:
	static void startGame() { _isGame = _Game::YES; }
	static void stopGame() { _isGame = _Game::NO; }
	Game(GConfigs &, std::vector<Strategy *> &);
	~Game() {}
	void Play();
	void Detailed();
	void Fast();
	void Tournament();
	void ResultsCalculating();
};