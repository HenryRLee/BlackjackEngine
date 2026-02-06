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
#include "Hand.h"
#include "GameTerm.h"

class Table;

using namespace GameTerm;

class Gambler
{
protected:
	string name;

	Table *table;
	vector <Hand> vHand;

	void GetOneCard(class Card, int hand=0);
	void CleanHands(void);

public:
	vector <Hand> ShowHand(int hand=0);
	string ShowName(void);

	virtual void JoinTable(Table *) = 0;
	void LeaveTable(void);

	Gambler(void);
	Gambler(string);
	virtual ~Gambler(void);

	friend class Game;
	friend class Table;
};
