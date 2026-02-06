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

#include "Table.h"
#include "Game.h"
#include "Player.h"
#include "Dealer.h"

void Table::AddDealer(Dealer * dealer)
{
	if (this->dealer == NULL)
		this->dealer = dealer;
}

void Table::AddPlayer(Player * player)
{
	vPlayer.push_back(player);
}

void Table::DelDealer(Dealer * dealer)
{
	if (this->dealer == dealer)
		this->dealer = NULL;
}

void Table::DelPlayer(Player * player)
{
	for (int i=0; i<vPlayer.size(); i++)
	{
		if (vPlayer[i] == player)
			vPlayer.erase(vPlayer.begin() + i);
	}
}

void Table::CleanTable(void)
{
	for (int i=0; i<vPlayer.size(); i++)
	{
		vPlayer[i]->CleanHands();
	}

	dealer->CleanHands();
}

void Table::GetOneCard(Card card)
{
	vUsedCard.GetOneCard(card);
}

void Table::CleanCards(void)
{
	vUsedCard.Clear();
}

UsedCard Table::ShowUsedCards(void)
{
	return vUsedCard;
}

void Table::UseGameType(Game * game)
{
	this->gametype = game;
}

void Table::StartOneGame(void)
{
	if ((dealer != NULL) && (vPlayer.size()>0))
		gametype->OneHandRoutine(dealer, vPlayer, this);
}

void Table::StartMultipleGames(long long num)
{
	if ((dealer != NULL) && (vPlayer.size()>0))
	{
		for (long long i=0; i<num; i++)
			gametype->OneHandRoutine(dealer, vPlayer, this);
	}
}

Table::Table(void)
{
	dealer = NULL;
}

Table::~Table(void)
{
}
