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
#include "Gambler.h"

class Strategy;
class BettingSystem;

class Player :
	public Gambler
{
protected:
	long long iBudget;

	Strategy * strategy;
	BettingSystem * bettingsystem;

	int SplitCards(int srchand);
	int MakeDecision(bitset<5> allowSet, int hand=0);

	void GetPays(double multiplier, int hand=0);

public:
	long long iBet;
	long long iPreferredBet;
	string ShowName(void);

	void SetBudget(long long);
	long long ShowBudget(void);

	void PreferBet(long long);
	void PlaceBet(int hand=0);
	void RaiseBet(long long, int hand=0);
	void DoubleBet(int hand=0);

	void JoinTable(Table *);

	void UseStrategy(Strategy *);
	void UseBettingSystem(BettingSystem *);

	Player(void);
	Player(string);
	~Player(void);

	friend class Game;
};
