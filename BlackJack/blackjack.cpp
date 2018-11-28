#include "blackjack.h"

const Card * Deck::start_deck = Deck::InitialDeck();

Card * Deck::InitialDeck() {
	Card * _deck = new Card[size];
	unsigned char i = 0u, j, cnt = 0u;
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

Deck::Deck(unsigned char n) : N(n) {
	deck = new Card[N * size];
	unsigned int i, tmp;
	for (i = 0u; i < (unsigned int)(N * size); i++) {
		deck[i] = start_deck[i % size];
	}
	srand(time(0));
	for (i = 0u; i < (unsigned int)(N * size); i++) {
		tmp = rand() % (N * size);
		if (tmp != i)
			std::swap(deck[i], deck[tmp]);
	}
}