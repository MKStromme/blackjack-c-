#include <string>

#include "card.hpp"

using namespace std;

int NBRSUITS = 4;
int HIGHCARD = 13;

card::card(int a, int b)
{
	if(a < NBRSUITS && a >= 0)
		suit = a;
	else
		return;
	if(b <= HIGHCARD && b > 0)
		value = b;
	else
		return;
}

bool card::is_court(void)
{
	if(value > 10)
		return true;
	else
		return false;
}

string card::to_string(void)
{
	string thisString = "";

	switch(value)
	{
		case 1:
			thisString += "Ace";
			break;
		case 11:
			thisString += "Jack";
			break;
		case 12:
			thisString += "Queen";
			break;
		case 13:
			thisString += "King";
			break;
		default:
			thisString += std::to_string(value);
	}

	thisString += " of ";

	switch(suit)
	{
		case 1:
			thisString += "Hearts";
			break;
		case 2:
			thisString += "Clubs";
			break;
		case 3:
			thisString += "Diamonds";
			break;
		default:
			thisString += "Spades";
	}
	return thisString;
}

int card::get_value()
{
	return value;
}
