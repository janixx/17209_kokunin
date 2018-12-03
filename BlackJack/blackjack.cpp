#include "blackjack.h"
#include "game.h"

//const Card * Deck::start_deck = Deck::InitialDeck();
//bool Deck::isDeckInit = false;

std::vector<Card> Deck::start_deck;
bool Deck::isDeckInit = false;

void Deck::PrintParam() {
	//std::ofstream out("file.txt");
	std::cout << (unsigned int)size << std::endl;
	std::cout << "\n";
	for (int i = 0; i < size; i++) {
		std::cout << "number: " << (unsigned int)start_deck[i].number << " weight: " <<
			(unsigned int)start_deck[i].weight <<
			" suit: " << (unsigned int)start_deck[i].suit << std::endl;
	}
	std::cout << "\n\n\n\n\n\n\n";
	std::cout << "Size of sorted deck is: " << (unsigned int)size * N << std::endl;
	std::cout << "\n";
	for (int i = 0; i < N * size; i++) {
		std::cout << "number: " << (unsigned int)deck[i].number << " weight: " <<
			(unsigned int)deck[i].weight <<
			" suit: " << (unsigned int)deck[i].suit << std::endl;
	}
}

Deck::Deck(unsigned char n, CardGivMode mode) : N(n) {
	topCard = N * size - 1u;
	deck.resize(topCard + 1u);
	unsigned int i;
	srand(unsigned int(time(0)));
	if (mode == CardGivMode::SIMPLE) {
		for (i = 0u; i <= topCard; i++) {
			deck[i].number = static_cast<unsigned char>(1 + rand() % 9);
			deck[i].weight = deck[i].number;
		}
		return;
	}
	else {
		unsigned int tmp;
		if (!Deck::isDeckInit)
			Deck::InitialDeck();

		for (i = 0u; i <= topCard; i++)
			deck[i] = start_deck[i % size];

		for (i = 0u; i <= topCard; i++) {
			tmp = rand() % (N * size);
			if (tmp != i)
				std::swap(deck[i], deck[tmp]);
		}
	}
}

Card & Deck::getCard() {
	return ((topCard > 1u) ? deck[topCard--] : deck[0u]);
}

void Deck::InitialDeck() {
	if (!isDeckInit) {
		start_deck.reserve(size);
		unsigned char i = 0u, j = 0u, cnt = 0u;
		for (; i < 4; i++) {
			for (j = 0u; j < size / 4; j++) {
				start_deck[cnt].number = j + (15 - size / 4);
				start_deck[cnt].suit = Suits(i);
				if (j == size / 4 - 1)
					start_deck[cnt].weight = 11;

				else if ((j >= size / 4 - 5) && (j <= size / 4 - 2))
					start_deck[cnt].weight = 10;

				else
					start_deck[cnt].weight = j + (15 - size / 4);

				cnt++;
			}
		}
	}
	isDeckInit = true;
}

GConfigs::GConfigs(GConfigs & other) : cMod(other.cMod), gMod(other.gMod),
configDir(other.configDir), deckSize(other.deckSize), countStr(other.countStr) {}

GConfigs::GConfigs() : cMod(CardGivMode::SIMPLE), gMod(GameMode::DETAILED)
, deckSize(1u), countStr(2u){}

GConfigs & GConfigs::operator=(const GConfigs & other) {
	if (this != &other) {
		cMod = other.cMod;
		gMod = other.gMod;
		deckSize = other.deckSize;
		countStr = other.countStr;
	}
	return *this;
}