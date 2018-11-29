#include "blackjack.h"

//const Card * Deck::start_deck = Deck::InitialDeck();
//bool Deck::isDeckInit = false;

void Deck::firstInit() {
	isDeckInit = false;
}

void Deck::InitialDeck() {
	if (!isDeckInit) {
		start_deck = new Card[size];
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
	return;
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

Deck::Deck() {
	topCard = 5u * size - 1u;
	deck = new Card[topCard + 1u];
	unsigned int i;
	srand(unsigned int(time(0)));
	for (i = 0u; i < (unsigned int)(N * size); i++) {
		deck[i].number = deck[i].weight = unsigned char(1 + rand() % 9);
		deck[i].suit = Suits(0);
	}
	return;
}

Deck::Deck(unsigned char n) : N(n) {
	topCard = N * size - 1u;
	deck = new Card[topCard + 1u];
	unsigned int i, tmp;
	srand(unsigned int(time(0)));

	if (!isDeckInit)
		InitialDeck();

	for (i = 0u; i < (unsigned int)(N * size); i++)
		deck[i] = start_deck[i % size];

	for (i = 0u; i < (unsigned int)(N * size); i++) {
		tmp = rand() % (N * size);
		if (tmp != i)
			std::swap(deck[i], deck[tmp]);
	}
}

Card & Deck::getCard() {
	if (topCard > 1u)
		return deck[topCard--];
	return deck[0u];
}