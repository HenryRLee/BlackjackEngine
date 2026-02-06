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

#include "EnhancedStrategy.h"
#include "Hand.h"
#include "Table.h"
#include "Dealer.h"

int EnhancedStrategy::MakeDecision(Hand hand, bitset <5> allowSet, Table table)
{
	int value = hand.GetScore();
	bool soft = hand.IsScoreSoft();
	vector <Hand> handDealer = table.dealer->ShowHand();
	int iDealerFaceup;
	int action;

	if (hand.vCard.size() < 2)
		return -1;

	if (handDealer.size() > 0)
		iDealerFaceup = handDealer[0].GetScore();
	else
		return -1;

	/* 16 vs 10 */
	if ((value == 16) && !soft && (iDealerFaceup == 10))
	{
		/* HIT vs STAND */
		const double original = 0.001449;
		const double delta[12] = 
		{
			0,			/* Not used */
			0,			/* Not used */
			-0.000491,	/* 2 */
			-0.001269,	/* 3 */
			-0.002728,	/* 4 */
			-0.003922,	/* 5 */
			0.002649,	/* 6 */
			-0.000998,	/* 7 */
			-0.000036,	/* 8 */
			0.000856,	/* 9 */
			0.001684,	/* 10 */
			-0.000729,	/* A */
		};
		UsedCard vUsedCard = table.ShowUsedCards();
		vector <Card> vCard = vUsedCard.ShowCards();
		double ev = original;

		if (allowSet[SURRENDER] == 1)
			return SURRENDER;

		/* Skip Dealer's card */
		for (int i=1; i<vCard.size(); i++)
		{
			int value = vCard[i].GetValue();

			if ((value >= 2) && (value <= 11))
				ev += delta[value];
		}

		if (ev >= 0)
			return HIT;
		else
			return STAND;
	}
	/* 14 vs 10 */
	else if ((value == 14) && !soft && (iDealerFaceup == 10))
	{
		/* HIT vs SURRENDER */
		const double original = -0.005379;
		const double delta[12] = 
		{
			0,			/* Not used */
			0,			/* Not used */
			-0.000442,	/* 2 */
			-0.000856,	/* 3 */
			-0.001549,	/* 4 */
			-0.002249,	/* 5 */
			-0.003667,	/* 6 */
			-0.004789,	/* 7 */
			0.001482,	/* 8 */
			0.001890,	/* 9 */
			0.002269,	/* 10 */
			0.001648,	/* A */
		};
		UsedCard vUsedCard = table.ShowUsedCards();
		vector <Card> vCard = vUsedCard.ShowCards();
		double ev = original;

		if (allowSet[SURRENDER] == 0)
			return HIT;

		/* Skip Dealer's card */
		for (int i=1; i<vCard.size(); i++)
		{
			int value = vCard[i].GetValue();

			if ((value >= 2) && (value <= 11))
				ev += delta[value];
		}

		if (ev >= 0)
			return HIT;
		else
			return SURRENDER;

	}
	else
	{
		return BasicStrategy::MakeDecision(hand, allowSet, table);
	}
}

EnhancedStrategy::EnhancedStrategy(void)
{
}

EnhancedStrategy::~EnhancedStrategy(void)
{
}
