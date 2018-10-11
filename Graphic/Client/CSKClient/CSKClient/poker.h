#pragma once
#include "main.h"
#include "card.h"

class Poker : public Card {
public:
	int id = -1;
	widgetObj *widget;

	Poker(Card c) : Card(c) {}
};

void addPoker(Poker p);
void removePoker(vector<int> idxs);
