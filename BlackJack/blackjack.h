#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

enum class Suits {
	HEART,
	DIAMOND,
	CLUB,
	SPARE
};

enum class Decision : unsigned char{
	STOP,
	NEXT
};


struct Card {
	unsigned char number;
	unsigned char weight;
	Suits suit;
};

class StackCard {
	std::stack<Card> stack_card;
	unsigned int weight_stack;
public:
	StackCard() : weight_stack(0u) {}
	StackCard(Card other) : weight_stack((unsigned int)other.weight) { stack_card.push(other); }
	~StackCard() {}
	Card & top(Card other) { return stack_card.top(); }
	void push(Card other) { stack_card.push(other); weight_stack += (unsigned int)other.weight; }
	void pop() { weight_stack -= (unsigned int)stack_card.top().weight; stack_card.pop(); }
	unsigned int size() { return (unsigned int)stack_card.size(); }
	unsigned int score() const { return weight_stack; }
	StackCard & operator=(const StackCard &) = delete;
};

class Deck {
private:
	const static unsigned char size = 36u;
	const static Card * start_deck;

	unsigned char N;
	Card * deck;
public:
	static Card * InitialDeck();
	Deck(unsigned char);
	~Deck() { delete[] start_deck; delete[] deck; }
	void PrintParam();
};

