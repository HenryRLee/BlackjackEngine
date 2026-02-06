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

#include "Gambler.h"

void Gambler::GetOneCard(Card card, int hand)
{
	if (vHand.size() < 1)
	{
		Hand firsthand;
		vHand.push_back(firsthand);
	}

	if (vHand.size() > hand)
	{
		vHand[hand].GetOneCard(card);
	}
}

void Gambler::CleanHands(void)
{
	for (int i=0; i<vHand.size(); i++)
	{
		vHand[i].CleanHands();
	}

	vHand.clear();

	if (vHand.size() < 1)
	{
		Hand firsthand;
		vHand.push_back(firsthand);
	}
}

void Gambler::LeaveTable(void)
{
	this->table = NULL;
}

vector <Hand> Gambler::ShowHand(int iHand)
{
	return vHand;
}

string Gambler::ShowName(void)
{
	return name;
}

Gambler::Gambler(void)
{
	Hand firsthand;
	vHand.push_back(firsthand);
}

Gambler::Gambler(string name)
{
	this->name = name;
}

Gambler::~Gambler(void)
{
}
