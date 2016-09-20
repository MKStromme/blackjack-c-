#ifndef CARD_H
#define CARD_H

#include <string>

class card
{
	private:
		int suit, value;
	
	public:
		card(int,int);
		bool is_court();
		std::string to_string();
		int get_value();
};

#endif
