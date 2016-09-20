#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include <string>

#include "card.hpp"

class person
{
	protected:
		std::vector<card> hand;
	public:
		person();
		void pick_card(std::vector<card> & deck, std::vector<card> & pile);
		void pick_card(std::vector<card> & deck, std::vector<card> & pile, int);
		int hand_value(void);
		card get_card_at(int);
		bool bust();
		void remove_hand(std::vector<card> & pile);
		std::string hand_string(void);

};

class player: public person
{
	private:
		bool stay;
		int credit;
		int pot;
		std::string name;
	public:
		player();
		std::string get_name(void);
		void set_name(std::string);
		bool get_stay(void);
		void set_stay(bool);
		int get_credit(void);
		void set_credit(int);//adds int to current credit.
		int get_pot(void);
		void set_pot(int);
};

class dealer: public person
{
	public:
		dealer();
		bool stop(void);
};
#endif
