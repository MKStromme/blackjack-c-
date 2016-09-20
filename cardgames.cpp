#include <vector>
#include <stdlib.h>
#include <time.h>

#include "cardgames.hpp"
#include "card.hpp"

namespace cardgames
{
	void create_deck(std::vector<card> & deck)
	{
		create_deck(deck, 1);
	}

	void create_deck(std::vector<card> & deck, int nbrDecks)
	{
		for(int i=0; i<nbrDecks;i++)
		{
			for(int j=0;j<4;j++)
			{
				for(int k=1; k<=13;k++)
				{
					deck.push_back(card(j,k));
				}
			}
		}
	}

	void shuffle(std::vector<card> & deck)
	{
		srand(time(NULL));
		for(int i=0;i<deck.size();i++)
		{
			swap(deck, i, rand()%(deck.size()-1));
		}
	}

	void swap(std::vector<card> & deck, int a, int b)
	{
		card temp = deck[b];
		deck[b] = deck[a];
		deck[a] = temp;
	}
}
