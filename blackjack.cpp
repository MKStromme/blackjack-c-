#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "card.hpp"
#include "person.hpp"
#include "cardgames.hpp"

using namespace std;

void quickStartGame(void);
vector<player>  playerList(int);
void initGame(void);
void gameSetting();
void newRound(void);
void endGame(void);
bool playerRound(player &);
bool dealerRound(void);
void emptyHands(void);
void playAnotherGame(void);
void placeBet(player &);
int inputNbr(void);

//declare deck, players and dealer in class scope.
//less work in this class, no difference when concerning other classes.

vector<card> deck, pile;
vector<player> players;
dealer theDealer;

int main(void)
{

	quickStartGame();
	theDealer = dealer();

	initGame();

	return 0;
}

void quickStartGame()
{
	cardgames::create_deck(deck);
	players = playerList(1);
	cardgames::shuffle(deck);
}

void gameSettings()
{
	string input;
	cout << "how many players?" << endl;
	cout << "enter number: ";
	cin >> input;
	players = playerList(stoi(input));
	input = "";
	cout << "how many decks do you want?" << endl;
	cout << "enter number; ";
	cin >> input;
	cardgames::create_deck(deck, stoi(input));
}

void initGame()
{
	string input;
	int bet;

	for(auto &i:players)
	{
		placeBet(i);
	}
	
	for(auto &i: players)
	{
		if(i.get_credit() > 0 || i.get_pot() > 0)
			i.pick_card(deck, pile, 2);
		else
			i.set_stay(true);
	}
	
	theDealer.pick_card(deck, pile, 2);
	
	for(auto i: players)
		cout << "you have: " << endl << i.hand_string();

	newRound();

}

void placeBet(player & kenny)
{
	int bet;
	
	cout << endl << endl;
	cout << "your current balance: " << kenny.get_credit() << endl;
	cout << "place a bet: ";
	bet = inputNbr();
	if(!(bet > 0))
	{
		cout << "your bet must be greater than 0." << endl;
		placeBet(kenny);
	}
	else if(bet > kenny.get_credit())
	{
		cout << "you cannot bet more than you have.";
		placeBet(kenny);
	}
	else
	{
		kenny.set_credit(bet*(-1));
		kenny.set_pot(bet);
	}
}

void newRound()
{
	cout << endl << "the dealer has: " << endl;
	cout << theDealer.get_card_at(0).to_string() << endl;

	for(auto &i: players)
	{
		playerRound(i);
	}
	dealerRound();

	endGame();
}

bool playerRound(player& thisPlayer)
{
	string in;

	if(!thisPlayer.get_stay())
	{
		if(!thisPlayer.bust())
		{
			cout << "'HIT' or 'STAY'?" << endl;
			cin >> in;
			if(in == "STAY" || in == "Stay" || in == "stay")
				thisPlayer.set_stay(true);
			else
			{
				thisPlayer.pick_card(deck, pile);
				
				cout << "you have: " << endl << endl;
				cout << thisPlayer.hand_string();

				playerRound(thisPlayer);
			}
		}
		else
			return false;
	}
	else 
		return false;
}

bool dealerRound()
{
	if(!theDealer.stop())
	{
		theDealer.pick_card(deck, pile);
		dealerRound();
	}
	else
		return false;
	return true;
}

void endGame()
{
	cout << "the winner is:" << endl;
	for(auto &i: players)
	{
		if(!i.bust())
		{
			if(i.hand_value() > theDealer.hand_value() 
					|| theDealer.bust())
			{	
				cout << i.get_name() << " has won." << endl;
				i.set_credit(i.get_pot()*2);
			}
		}
		i.set_pot(0);
		i.set_stay(false);
	}
	emptyHands();
	playAnotherGame();
}

void playAnotherGame()
{
	string in;
	bool justOneMoreTurn = true;
	for(auto i: players)
		justOneMoreTurn &= i.get_credit() > 0;
	if(!justOneMoreTurn)
	{
		cout << "one or more players don't have the credit to continue";
		cout << endl;
		return;
	}
	cout << "would you like to play again? (y/n)" << endl;
	cin >> in;
	if(in == "y" || in == "Y" || in == "yes" || in == "YES" || in == "Yes")
	{
		cout << "here we go" << endl;
		initGame();
	}
	else
	{
		cout << "come again." << endl;
		return;
	}
}

void emptyHands()
{
	for(auto &i: players)
		i.remove_hand(pile);
	theDealer.remove_hand(pile);
}

vector<player> playerList(int a)
{
	vector<player> newPlayerList;
	for(int i = 0; i < a; i++)
		newPlayerList.push_back(player());
	return newPlayerList;
}

int inputNbr()
{
	try
	{
		string a;
		cin >> a;
		return stoi(a);
	}
	catch(logic_error e)
	{
		cout << "input a number: " << endl;
		inputNbr();
	}
}
