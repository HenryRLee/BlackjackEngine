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

#include "Hand.h"

int Hand::GetScore(void)
{
	return iScore;
}

bool Hand::IsScoreSoft(void)
{
	if (iSoftScore > 0)
		return true;
	else
		return false;
}

void Hand::GetOneCard(Card card)
{
	int value;

	value = card.GetValue();
	vCard.push_back(card);
	iScore += value;

	if (value == 11)
		iSoftScore++;

	while ((iScore>MaxScore) && (iSoftScore>0))
	{
		iSoftScore--;
		iScore -= 10;
	}

}

Card Hand::RemoveLastCard(void)
{
	int value;
	Card pop = vCard.back();

	vCard.pop_back();

	/* Because the Ace value varies, we have to recount the value from start. */
	iScore = 0;
	iSoftScore = 0;

	for (int i=0; i<vCard.size(); i++)
	{
		value = vCard[i].GetValue();
		iScore += value;

		if (value == 11)
			iSoftScore++;

		while ((iScore>MaxScore) && (iSoftScore>0))
		{
			iSoftScore--;
			iScore -= 10;
		}
	}

	return pop;
}

void Hand::CleanHands(void)
{
	vCard.clear();
	iScore = 0;
	iBet = 0;
	iStatus = WAITING;
	iSoftScore = 0;
}

Hand::Hand(void)
{
	vCard.clear();
	iScore = 0;
	iBet = 0;
	iStatus = WAITING;
	iSoftScore = 0;
}

Hand::~Hand(void)
{
}
