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

#include "Blackjack.h"
#include "Player.h"
#include "Dealer.h"
#include "Table.h"
#include "MacauSimulation.h"
#include "StreamLog.h"
#include "LongTermStats.h"
#include "NoStrategy.h"
#include "BasicStrategy.h"
#include "EnhancedStrategy.h"
#include "FixedBet.h"
#include "FlowCounting.h"
#include "SydneySimulation.h"

inline int RunMultipleGames(long long times, Table * table, Player * player,
		Statistics * stat=NULL)
{
	long long peak = player->ShowBudget();
	long long dip = player->ShowBudget();

	for (long long i=0; i<times; i++)
	{
		long long current;
		
		table->StartOneGame();

		current = player->ShowBudget();

		peak = (peak > current) ? peak : current;
		dip = (dip < current) ? dip : current;
	}

	cout << "Peak: " << peak << "\tDip: " << dip;
	cout << "\tCurrent: " << player->ShowBudget();
	cout << endl;

	return 0;
}

int main(int argc, char *argv[])
{
	Player * Hank = new Player("Hank");
	Dealer * BJDealer = new Dealer("BJDealer");
	Table * Venetian = new Table;
	Game * MacauGame = new MacauSimulation;
	Game * SydneyGame = new SydneySimulation;
	Statistics * NoLogger = new LongTermStats;
	Statistics * Logger = new StreamLog;
	Strategy * UserInput = new NoStrategy;
	Strategy * BStrategy = new BasicStrategy;
	Strategy * EStrategy = new EnhancedStrategy;
	BettingSystem * Fixedbet = new FixedBet;
	BettingSystem * Flowcounting = new FlowCounting;

//	Hank->UseStrategy(EStrategy);
	Hank->UseStrategy(BStrategy);
//	Hank->UseStrategy(UserInput);
	Hank->UseBettingSystem(Fixedbet);
	Hank->UseBettingSystem(Flowcounting);
	Hank->PreferBet(1000);
	Hank->SetBudget(0);
	BJDealer->JoinTable(Venetian);
	MacauGame->UseStatistics(NoLogger);
	SydneyGame->UseStatistics(NoLogger);
//	MacauGame->UseStatistics(Logger);
	Venetian->UseGameType(MacauGame);
//	Venetian->UseGameType(SydneyGame);

	/* Add multiple players */
	Player * Passenger[10];
	for (int i=0; i<0; i++)
	{
		Passenger[i] = new Player("Passenger");
		Passenger[i]->JoinTable(Venetian);
		Passenger[i]->UseStrategy(BStrategy);
		Passenger[i]->PreferBet(100);
		Passenger[i]->SetBudget(0);
	}

	Hank->JoinTable(Venetian);
	Venetian->CleanTable();
//	Venetian->StartOneGame();

	cout << fixed;
	cout.precision(0);

//	Venetian->StartMultipleGames(10);

	for (int i=0; i<1000; i++)
	{
		srand(time(NULL));
		cout << "Round: " << i+1 << "\t";
		RunMultipleGames(1000, Venetian, Hank);
	}

	cout << "Final budget " << Hank->ShowBudget() << endl;

	return 0;
}
