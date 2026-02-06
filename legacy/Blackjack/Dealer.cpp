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

#include "Dealer.h"
#include "Table.h"

string Dealer::ShowName(void)
{
	return "[Dealer]" + name;
}

void Dealer::JoinTable(Table * table)
{
	table->AddDealer(this);

	this->table = table;
}

int Dealer::MakeDecision(bool bHitOnSoft17, int iHand)
{
	if (vHand.size() > iHand)
	{
		int score;
		score = vHand[iHand].GetScore();

		if (score < 17)
		{
			return HIT;
		}
		else if (score > 17)
		{
			return STAND;
		}
		else if (score == 17)
		{
			if (!vHand[iHand].IsScoreSoft())
			{
				return STAND;
			}
			else
			{
				if (bHitOnSoft17)
					return HIT;
				else
					return STAND;
			}
		}
	}

	return -1;
}

void Dealer::GetHoleCard(Card hole)
{
	this->cardHole = hole;
}

/* Return true if it's Blackjack */
bool Dealer::PeakHoldCard(void)
{
	if (vHand.size() >= 1)
	{
		if ((cardHole.GetValue() + vHand[0].GetScore()) == MaxScore)
			return true;
		else
			return false;
	}

	return false;
}

Card Dealer::ShowHoleCard(void)
{
	GetOneCard(cardHole);

	return cardHole;
}

Dealer::Dealer(void)
{
}

Dealer::Dealer(string name)
{
	this->name = name;
}

Dealer::~Dealer(void)
{
}
