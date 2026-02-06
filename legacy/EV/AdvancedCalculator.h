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
#include "SimpleCalculator.h"

class AdvancedCalculator :
	public SimpleCalculator
{
protected:
	vector <int> vInitialCount;
	void InitiateCardCounts(UsedCard *);
	vector <int> CardFlowing(int value, vector <int> vRemaining);

	double ProbOfGettingCard(int value);
	double ProbOfGettingCard(int value, vector <int> vRemaining);

	ProbSet ProbOfHandsDealerTurn(HandScore player, HandScore dealer,
			vector <int> vRemaining);
	ProbSet ProbOfHandsDealerFirstTurn(HandScore player, HandScore dealer,
			vector <int> vRemaining);

	ProbSet ProbOfHandsPlayerTurn(HandScore player, HandScore dealer, 
			vector <int> vRemaining, int action=NONE);

	ProbSet ProbOfHandsPlayerHit(HandScore player, HandScore dealer);
	ProbSet ProbOfHandsPlayerStand(HandScore player, HandScore dealer);
	ProbSet ProbOfHandsPlayerHitOrStand(HandScore player, HandScore dealer);
	ProbSet ProbOfHandsPlayerDouble(HandScore player, HandScore dealer);

	ProbSet ProbAfterGettingCard(ProbSet current, ProbSet next, int iCardValue,
			vector <int> vRemaining);

public:
	void ShowProbSetByAction(int iPlayerScore, bool bPlayerSoft, 
			int iDealerScore, bool bDealerSoft, int action=0,
			UsedCard * usedcard=NULL);

	void ShowProbSetByNextCard(int iPlayerScore, bool bPlayerSoft, 
			int iDealerScore, bool bDealerSoft, int action=0,
			UsedCard * usedcard=NULL);

	void ShowDeltaOfEachTakenCard(int iPlayerScore, bool bPlayerSoft,
			int iDealerScore, bool bDealerSoft, int iFirstAction=HIT,
			int iSecondAction=STAND, UsedCard * usedcard=NULL);

	AdvancedCalculator(void);
	~AdvancedCalculator(void);
};
