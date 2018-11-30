#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <iostream>
#ifndef BLACKJACK_H
#define BLACKJACK_H
enum class Suits {
	HEART,
	DIAMOND,
	CLUB,
	SPARE
};

enum class Decision : bool {
	STOP = 0x0,
	NEXT = 0x1
};


struct Card {
	unsigned char number;
	unsigned char weight;
	Suits suit;
};

class Deck {
private:
	const static unsigned char size = 36u;
	static std::vector<Card> start_deck;
	static bool isDeckInit;

	unsigned char N;
	unsigned int topCard;
	std::vector<Card> deck;
public:
	static void InitialDeck();
	static void firstInit() { isDeckInit = false; }
	Deck(unsigned char);
	Deck();
	~Deck() {}
	Card & getCard();
	void PrintParam();
};

class StackCard {
	std::stack<Card> stack_card;
	unsigned int weight_stack = 0u;
public:
	StackCard() : weight_stack(0u) {}
	StackCard(Card & other) : weight_stack(static_cast<unsigned int>(other.weight)) { stack_card.push(other); }
	~StackCard() {}
	Card & top() { return stack_card.top(); }
	void push(Card & other) { stack_card.push(other); weight_stack += (unsigned int)other.weight; }
	void pop() { weight_stack -= (unsigned int)stack_card.top().weight; stack_card.pop(); }
	unsigned int size() { return (unsigned int)stack_card.size(); }
	unsigned int score() const { return weight_stack; }
	StackCard & operator=(const StackCard &) = delete;
};

#endif