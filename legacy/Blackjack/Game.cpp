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

#include "Game.h"
#include "Table.h"
#include "Player.h"
#include "Dealer.h"
#include "ShuffleMachine.h"
#include "Statistics.h"

void inline Game::DealInitialCards(Dealer * dealer, 
		vector <class Player *> vPlayer, Table * table)
{
	Card pop;

	pop = shuffler->PopOneCard(table);
	dealer->GetOneCard(pop);

	if (bDealerTakesHole)
	{
		pop = shuffler->PopOneCard(table);
		dealer->GetHoleCard(pop);
	}

	for (int i=0; i<vPlayer.size(); i++)
	{
		pop = shuffler->PopOneCard(table);
		vPlayer[i]->GetOneCard(pop);

		pop = shuffler->PopOneCard(table);
		vPlayer[i]->GetOneCard(pop);
	}
}

void inline Game::DealOneCard(Gambler * gambler, Table * table, int hand)
{
	Card pop;
	
	pop = shuffler->PopOneCard(table);
	gambler->GetOneCard(pop, hand);
}

void Game::PlayerAction(Player * player, bitset<5> allowSet, int iHand)
{
	int action;
	Hand * handCurrent = &(player->vHand[iHand]);

	if (player->vHand.size() <= iHand)
	{
		cout << "Error occured" << endl;
		return;
	}

	if (handCurrent->vCard.size() >= 2)
	{
		if (handCurrent->vCard[0].GetValue() != 
			handCurrent->vCard[1].GetValue())
		{
			allowSet.set(SPLIT, 0);
		}
	}
	else
	{
		cout << "Error occured" << endl;
	}

	statistics->Update(*handCurrent);
	action = player->MakeDecision(allowSet, iHand);

	if (allowSet[action] == 0)
	{
		statistics->Update("Action not available");
		PlayerAction(player, allowSet, iHand);
	}

	switch (action)
	{
	case HIT:
		allowSet.set(SURRENDER, 0);
		allowSet.set(DOUBLE, 0);
		allowSet.set(SPLIT, 0);

		DealOneCard(player, table, iHand);

		if (handCurrent->GetScore() > MaxScore)
			handCurrent->iStatus = BUSTED;
		else
			PlayerAction(player, allowSet, iHand);
		break;

	case STAND:
		handCurrent->iStatus = WAITING;
		break;

	case DOUBLE:
		allowSet.set(HIT, 0);
		allowSet.set(DOUBLE, 0);
		allowSet.set(DOUBLE, 0);
		allowSet.set(SURRENDER, 0);
		allowSet.set(SPLIT, 0);

		player->DoubleBet(iHand);
		DealOneCard(player, table, iHand);

		if (handCurrent->GetScore() > MaxScore)
		{
			handCurrent->iStatus = BUSTED;
		}
		else
		{
			handCurrent->iStatus = DOUBLEDWAITING;
		}

		break;

	case SURRENDER:
		handCurrent->iStatus = SURRENDERED;

		break;

	case SPLIT:
		int iSplittedHand;
		iSplittedHand = player->SplitCards(iHand);

		if (!bHitAfterSplit)
		{
			allowSet.set(HIT, 0);
			allowSet.set(DOUBLE, 0);
			allowSet.set(SPLIT, 0);
		}
		else
		{
			if (bStandAfterSplittedAces)
			{
				allowSet.set(HIT, 0);
				allowSet.set(DOUBLE, 0);
				allowSet.set(SPLIT, 0);
			}

			if (!bDoubleAfterSplit)
				allowSet.set(DOUBLE, 0);

			if (!bSplitAfterSplit)
				allowSet.set(SPLIT, 0);
			else if (iSplittedHand >= iTimesSplittedAllow)
				allowSet.set(SPLIT, 0);
			else if ((!bResplitAces) && (player->vHand[iHand].vCard[0].GetValue()==11))
				allowSet.set(SPLIT, 0);
		}

		allowSet.set(SURRENDER, 0);

		DealOneCard(player, table, iHand);
		PlayerAction(player, allowSet, iHand);

		player->PlaceBet(iSplittedHand);
		DealOneCard(player, table, iSplittedHand);
		PlayerAction(player, allowSet, iSplittedHand);

		break;

	default:
		cout << "Error occured" << endl;
		break;
	}
}

void Game::DealerAction(Dealer * dealer)
{
	int action;

	if (dealer->vHand.size() <= 0)
	{
		cout << "Error occured" << endl;
		return;
	}

	action = dealer->MakeDecision(bHitOnSoft17);

	switch (action)
	{
	case HIT:
		DealOneCard(dealer, table);

		if (dealer->vHand[0].GetScore() > MaxScore)
			dealer->vHand[0].iStatus = BUSTED;
		else
			DealerAction(dealer);

		break;

	case STAND:
		break;

	default:
		cout << "Error occured" << endl;
		break;
	}
}

void Game::OneHandRoutine(Dealer * dealer, vector <class Player *> vPlayer,
		Table * table)
{
	Card cardPop;

	this->table = table;

	if (table == NULL)
		return;

	table->CleanTable();

	for (int i=0; i<vPlayer.size(); i++)
		vPlayer[i]->PlaceBet();

	shuffler->ShuffleCards(table);

	DealInitialCards(dealer, vPlayer, table);

	statistics->Update(table, "Dealt initial cards");
	statistics->Update(" ");

	if (bDealerTakesHole && bDealerPeaksHole)
	{
		bool bBlackjack = false;

		if (bDealerPeaksHoleOnAce && (dealer->vHand[0].GetScore() == 11))
		{
			if (dealer->PeakHoldCard())
				bBlackjack = true;
		}
		if (bDealerPeaksHoleOnTen && (dealer->vHand[0].GetScore() == 10))
		{
			if (dealer->PeakHoldCard())
				bBlackjack = true;
		}

		if (bBlackjack)
		{
			/* Dealer has a Blackjack */
			dealer->ShowHoleCard();
			dealer->vHand[0].iStatus = BJ;

			statistics->Update(" ");
			statistics->Update(dealer, "Final hands");
			statistics->Update(" ");

			for (int i=0; i<vPlayer.size(); i++)
			{
				statistics->Update(vPlayer[i], "Final hands");

				if (vPlayer[i]->vHand[0].GetScore() == MaxScore)
				{
					vPlayer[i]->vHand[0].iStatus = BJ;
					statistics->Update("  BOTH BLACKJACKS");
					vPlayer[i]->vHand[0].iStatus = PUSH;
					vPlayer[i]->GetPays(1, 0);
				}
				else
				{
					statistics->Update("  DEALER HAS A BLACKJACK");
					vPlayer[i]->vHand[0].iStatus = LOST;
				}
			}

			statistics->Update(" ");
			statistics->Update(table, "Game complete");
			statistics->Update(" ");

			return;
		}
	}

	for (int i=0; i<vPlayer.size(); i++)
	{
		bitset <5> allowSet;

		if (vPlayer[i]->vHand[0].GetScore() == MaxScore)
		{
			/* Blackjack */
			vPlayer[i]->vHand[0].iStatus = BJ;

			continue;
		}

		allowSet.set(HIT);
		allowSet.set(STAND);

		if (bDouble)
		{
			if (bDoubleOnAnyTwo)
			{
				allowSet.set(DOUBLE);
			}
			else
			{
				if (bDoubleOnNine && (vPlayer[i]->vHand[0].GetScore() == 9))
					allowSet.set(DOUBLE);
				if (bDoubleOnTen && (vPlayer[i]->vHand[0].GetScore() == 10))
					allowSet.set(DOUBLE);
				if (bDoubleOnEleven && (vPlayer[i]->vHand[0].GetScore() == 11))
					allowSet.set(DOUBLE);
			}
		}

		if (bSurrender)
		{
			allowSet.set(SURRENDER);

			if (!bSurrenderVsDealerAce)
			{
				if (dealer->vHand.size() > 0)
				{
					if (dealer->vHand[0].vCard.size() > 0)
					{
						if (dealer->vHand[0].vCard[0].GetValue() == 11)
							allowSet.set(SURRENDER, 0);
					}
				}
			}
		}

		if (bSplit)
			allowSet.set(SPLIT);

		PlayerAction(vPlayer[i], allowSet);
	}

	if (bDealerTakesHole)
		dealer->ShowHoleCard();
	else
		DealOneCard(dealer, table);

	if ((dealer->vHand[0].vCard[0].GetValue() +
				dealer->vHand[0].vCard[1].GetValue()) == MaxScore)
	{
		/* Blackjack */
		dealer->vHand[0].iStatus = BJ;
	}
	else
	{
		DealerAction(dealer);
	}

	statistics->Update(" ");
	statistics->Update(dealer, "Final hands");
	statistics->Update(" ");

	if (dealer->vHand.size() > 0)
	{
		for (int i=0; i<vPlayer.size(); i++)
		{
			statistics->Update(vPlayer[i], "Final hands");
			for (int j=0; j<vPlayer[i]->vHand.size(); j++)
			{
				if (vPlayer[i]->vHand[j].iStatus == BJ)
				{
					if (dealer->vHand[0].iStatus == BJ)
					{
						vPlayer[i]->GetPays(1);
						statistics->Update("  BOTH BLACKJACKS");
					}
					else
					{
						vPlayer[i]->GetPays(dBlackJackPays);
						statistics->Update("  PLAYER HAS A BLACKJACK");
					}

				}
				else if (vPlayer[i]->vHand[j].iStatus == SURRENDERED)
				{
					vPlayer[i]->GetPays(0.5, j);

					statistics->Update("  PLAYER SURRENDERS");
				}
				else if (dealer->vHand[0].iStatus == BJ)
				{
					/* 
					 * If Dealer has a Blackjack, player loses even if he has a
					 * 21. However, some rules may allow player lose original
					 * bet only when doubling and splitting.
					 */
					if (vPlayer[i]->vHand[j].iStatus == DOUBLEDWAITING)
					{
						/* Double loses original bet */
						if (bDOBO)
						{
							if (!bSOBO || (j==0))
							{
								vPlayer[i]->GetPays(0.5, j);
								vPlayer[i]->vHand[j].iStatus = LOST;
								statistics->Update("  OBO IN DOUBLE");
							}
							else
							{
								/* Splitted hand. Will be handled later. */
							}
						}
					}

					if ((bSOBO) && (j>0))
					{
						/* Splitted hand. Pay back all */
						vPlayer[i]->GetPays(1, j);
						vPlayer[i]->vHand[j].iStatus = PUSH;
						statistics->Update("  OBO IN SPLIT");
					}
					else
					{
						vPlayer[i]->vHand[j].iStatus = LOST;
						statistics->Update("  DEALER HAS A BLACKJACK");
					}
				}
				else if (vPlayer[i]->vHand[j].iStatus == BUSTED)
				{
					vPlayer[i]->vHand[j].iStatus = LOST;

					statistics->Update("  PLAYER BUSTS");
				}
				else if (dealer->vHand[0].iStatus == BUSTED)
				{
					vPlayer[i]->vHand[j].iStatus = WON;
					vPlayer[i]->GetPays(2, j);

					statistics->Update("  DEALER BUSTS");
				}
				else if (vPlayer[i]->vHand[j].GetScore() > dealer->vHand[0].GetScore())
				{
					vPlayer[i]->vHand[j].iStatus = WON;
					vPlayer[i]->GetPays(2, j);

					statistics->Update("  PLAYER WINS");
				}
				else if (vPlayer[i]->vHand[j].GetScore() == dealer->vHand[0].GetScore())
				{
					vPlayer[i]->vHand[j].iStatus = PUSH;
					vPlayer[i]->GetPays(1, j);

					statistics->Update("  PUSH");
				}
				else if (vPlayer[i]->vHand[j].GetScore() < dealer->vHand[0].GetScore())
				{
					vPlayer[i]->vHand[j].iStatus = LOST;

					statistics->Update("  PLAYER LOSES");
				}
			}
		}
	}
					
	statistics->Update(" ");
	statistics->Update(table, "Game complete");
	statistics->Update(" ");

	this->table = NULL;
}

void Game::UseStatistics(Statistics * statistics)
{
	this->statistics = statistics;
}

Game::Game(void)
{
}

Game::~Game(void)
{
}
