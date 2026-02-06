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
#include "GameTerm.h"

using namespace GameTerm;

class Table;
class Gambler;
class Player;
class Dealer;
class ShuffleMachine;
class Statistics;

class Game
{
protected:
	Table * table;
	ShuffleMachine * shuffler;
	Statistics * statistics;

	bool bHitOnSoft17;
	bool bDouble;
	bool bSurrender;
	bool bSplit;
	bool bDealerTakesHole;
	bool bDealerPeaksHole;
	bool bDealerPeaksHoleOnAce;
	bool bDealerPeaksHoleOnTen;
	bool bHitAfterSplit;
	bool bDoubleAfterSplit;
	bool bDoubleOnAnyTwo;
	bool bDoubleOnNine;
	bool bDoubleOnTen;
	bool bDoubleOnEleven;
	bool bSplitAfterSplit;
	bool bResplitAces;
	bool bStandAfterSplittedAces;
	bool bLateSurrender;
	bool bSurrenderVsDealerAce;
	/* Lose only orignal bet in double when dealer has a Blackjack */
	bool bDOBO;
	/* Lose only orignal bet in split when dealer has a Blackjack */
	bool bSOBO;
	int iTimesSplittedAllow;
	double dBlackJackPays;

	void inline DealInitialCards(Dealer *, vector <class Player *>,
			Table * table);
	void inline DealOneCard(Gambler *, Table * table, int hand=0);
	void PlayerAction(Player *, bitset<5> allowSet, int hand=0);
	void DealerAction(Dealer *);

	void OneHandRoutine(Dealer * , vector <class Player *>, Table *);

public:

	void UseStatistics(Statistics *);

	Game(void);
	virtual ~Game(void);

	friend class Table;
};
