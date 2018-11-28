#include "blackjack.h"

//const Card * Deck::start_deck = Deck::InitialDeck();

Card * Deck::InitialDeck(bool simple) {
	if (!simple) {
		Card * _deck = new Card[size];
		unsigned char i = 0u, j = 0u, cnt = 0u;
		for (; i < 4; i++) {
			for (j = 0u; j < size / 4; j++) {
				_deck[cnt].number = j + (15 - size / 4);
				_deck[cnt].suit = Suits(i);
				if (j == size / 4 - 1)
					_deck[cnt].weight = 11;
				else if ((j >= size / 4 - 5) && (j <= size / 4 - 2))
					_deck[cnt].weight = 10;
				else
					_deck[cnt].weight = j + (15 - size / 4);
				cnt++;
			}
		}
		return _deck;
	}
	return nullptr;
}

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

Deck::Deck(unsigned char n, bool simple) : N(n) {
	deck = new Card[N * size];
	unsigned int i, tmp;
	srand(time(0));
	if (simple) {
		for (i = 0u; i < (unsigned int)(N * size); i++) {
			deck[i].number = deck[i].weight = unsigned char(1 + rand() % 9);
			deck[i].suit = Suits(0);
		}
		return;
	}

	for (i = 0u; i < (unsigned int)(N * size); i++)
		deck[i] = start_deck[i % size];

	for (i = 0u; i < (unsigned int)(N * size); i++) {
		tmp = rand() % (N * size);
		if (tmp != i)
			std::swap(deck[i], deck[tmp]);
	}
}