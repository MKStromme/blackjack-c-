GPP=g++
GPPOPT=-std=c++11

OBJ=blackjack

all: $(OBJ)

blackjack:
	$(GPP) $(GPPOPT) card.cpp person.cpp cardgames.cpp  blackjack.cpp -o $@


clean: 
	-$(RM) $(OBJ)
