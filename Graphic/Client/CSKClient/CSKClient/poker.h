#pragma once
#include "main.h"
#include "card.h"

class Poker : public Card {
public:
	int id = -1;
	Poker(Card c) : Card(c) {}
};

void addPoker(Poker p);