#include "game.h"

Game::Game(unsigned int count, GConfigs mode, std::vector<Strategy*> & str)
	: strategies(str) : _isGame(_Game::NO) {
	if(mode.cMod == CardGivMode::SIMPLE)
		const Card * Deck::start_deck = Deck::InitialDeck(CardGivMode::SIMPLE);

}
