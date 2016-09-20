#include <vector>
#include <string>
#include <stdexcept>

#include "card.hpp"
#include "person.hpp"
#include "cardgames.hpp"

using namespace std;

person::person()
{
	vector<card> hand;
}

void person::pick_card(vector<card> & deck, vector<card> & pile)
{
	pick_card(deck, pile, 1);
}

void person::pick_card(vector<card> & deck, vector<card> & pile, int a)
{
	for(int i = 0; i < a; i++)
	{
		if(deck.size() > 0)
		{
			hand.push_back(deck.back());
			deck.pop_back();
		}
		else
		{
			deck.insert(deck.end(), pile.begin(), pile.end());
			cardgames::shuffle(deck);
		}
	}
}

int person::hand_value(void)
{
	int handValue=0;
	int nbrAce=0;
	for(auto i: hand)
	{
		if(i.get_value()==1)
		{
			handValue += 11;
			nbrAce++;
		}
		else if(i.is_court())
			handValue+=10;
		else
			handValue+=i.get_value();
	}
	if(handValue>21 && nbrAce > 0)
	{
		for(int i = 0; i < nbrAce; i++)
			handValue -= 10;
	}
	return handValue;
}

string person::hand_string()
{
	string returnString = "";
	for(auto i: hand)
		returnString += i.to_string() + "\n";
	return returnString;
}


bool person::bust (void)
{
	return hand_value() > 21;
}

card person::get_card_at(int a)
{
	if(a < hand.size()) 
		return hand[a];
	else
		throw runtime_error("ingen kort på denne plassen");
}

void person::remove_hand(vector<card> & pile)
{
	pile.insert(pile.end(),hand.begin(),hand.end());
	hand.erase(hand.begin(),hand.end());
}

player::player()
{
	person();
	stay = false;
	credit = 500;
	pot = 0;
	name = "Kenny Rogers";
}

string player::get_name()
{
	return name;
}

void player::set_name(string a)
{
	name = a;
}

int player::get_pot(void)
{
	return pot;
}

void player::set_pot(int a)
{
	pot = a;
}

bool player::get_stay(void)
{
	return stay;
}

void player::set_stay(bool a)
{
	stay=a;
}

int player::get_credit()
{
	return credit;
}

void player::set_credit(int a)
{
		credit += a;
}

dealer::dealer()
{
	person();
}

bool dealer::stop(void)
{
	return hand_value() >= 17;
}
