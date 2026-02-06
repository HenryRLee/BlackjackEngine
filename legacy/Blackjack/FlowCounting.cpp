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

#include "FlowCounting.h"
#include "Table.h"

long long FlowCounting::CalculateBet(long long iPreferredBet, long long iBudget,
		Table *table)
{
	if (table)
	{
		long long iFinalBet;
		int iCardValue[12] =
		{
			0,
			0,
			79,
			89,
			115,
			148,
			87,
			56,
			-56,
			-44,
			-104,
			-122
		};
		int iFlowValue = 0;
		UsedCard vUsedCard = table->ShowUsedCards();
		vector <Card> vCard = vUsedCard.ShowCards();

		for (int i=0; i<vCard.size(); i++)
		{
			int score = vCard[i].GetValue();
			if (score <= 11)
				iFlowValue += iCardValue[score];
		}

		if (iFlowValue < 200)
			iFinalBet = 0;
		else
			iFinalBet = iPreferredBet * (iFlowValue / 100) + 0 * (1 + iPreferredBet/1000);

		return iFinalBet;
	}
	else
	{
		return iPreferredBet;
	}
}

FlowCounting::FlowCounting(void)
{
}

FlowCounting::~FlowCounting(void)
{
}
