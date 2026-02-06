/*
 *  Copyright 2016 Henry Lee
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once
#include "Blackjack.h"
#include "Card.h"
#include "UsedCard.h"

class ShuffleMachine;
class Dealer;
class Player;
class Game;

class Table
{
private:
	Game * gametype;

	UsedCard vUsedCard;

	void AddDealer(Dealer *);
	void AddPlayer(Player *);
	void DelDealer(Dealer *);
	void DelPlayer(Player *);

public:
	Dealer * dealer;
	vector <class Player *> vPlayer;

	void CleanTable(void);

	void GetOneCard(Card card);
	void CleanCards(void);
	UsedCard ShowUsedCards(void);

	void UseGameType(Game *);
	void StartOneGame(void);
	void StartMultipleGames(long long num=1000);

	Table(void);
	~Table(void);

	friend class Player;
	friend class Dealer;
};
