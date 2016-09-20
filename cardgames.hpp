#include <vector>

#include "card.hpp"

namespace cardgames
{
	void create_deck(std::vector<card> & deck);
	void create_deck(std::vector<card> & deck, int);
	
	void shuffle(std::vector<card> & deck);
	void swap(std::vector<card> & deck, int, int);
};
