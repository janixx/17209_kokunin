#ifndef BLACKJACK_H

#define BLACKJACK_H
#include <cstdlib>
#include <ctime>
#include <stack>
#include <map>
#include <vector>

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
	std::string configDir;
	unsigned char deckSize;
	unsigned int countStr;

	GConfigs(GConfigs & other);
	GConfigs();
	GConfigs & operator=(const GConfigs & other);
};

enum class Suits {
	HEART,
	DIAMOND,
	CLUB,
	SPARE
};

enum class Decision : bool {
	STOP = 0x1,
	NEXT = 0x0
};


struct Card {
	unsigned char number;
	unsigned char weight;
	Suits suit;
};

class Deck {
public:
	Deck(unsigned char n = 1u, CardGivMode mode = CardGivMode::SIMPLE);
	const Card & getCard();
//	void PrintParam();

	static void InitialDeck();
private:
	const static unsigned char size = 36u;
	static std::vector<Card> start_deck;

	unsigned char N = 1u;
	unsigned int topCard;
	std::vector<Card> deck;
};

class StackCard {
	std::stack<Card> stack_card;
	unsigned int weight_stack = 0u;
public:
	StackCard() : weight_stack(0u) {}
	~StackCard() {}
	Card & top() { return stack_card.top(); }
	void push(const Card & other) { stack_card.push(other) ; weight_stack += (unsigned int)other.weight; }
	void pop() { weight_stack -= (unsigned int)stack_card.top().weight; stack_card.pop(); }
	unsigned int size() const { return (unsigned int)stack_card.size(); }
	unsigned int score() const { return weight_stack; }

	StackCard(const Card & other) = delete;
	StackCard & operator=(const StackCard &) = delete;
};

#endif