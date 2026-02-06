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

#include "ManipulatedCardSequence.h"
#include <random>

Card ManipulatedCardSequence::PopOneCard(void)
{
	Card cardPop;

	cardPop = vCard[0];

	vUsedCard.push_back(vCard[0]);
	vCard.erase(vCard.begin());

	return cardPop;
}

void ManipulatedCardSequence::ShuffleCards(void)
{
	for (int i=0; i<vUsedCard.size(); i++)
	{
		vCard.push_back(vUsedCard[i]);
	}

	vUsedCard.clear();
}

void ManipulatedCardSequence::TakeSpecificCard(int value, int num)
{
}

ManipulatedCardSequence::ManipulatedCardSequence(void)
{
	int iSequence[] = {11, 11, 11, 10, 10, 10};

	vCard.clear();
	vUsedCard.clear();

	for (int i=0; i<(sizeof(iSequence)/sizeof(int)); i++)
	{
		char name[8] = "";
		if (iSequence[i] == 11)
			snprintf(name, sizeof(name), "AinD");
		else
			snprintf(name, sizeof(name), "%dinD", iSequence[i]);

		Card card(0, iSequence[i], name);
		vCard.push_back(card);
	}
}

ManipulatedCardSequence::~ManipulatedCardSequence(void)
{
}
