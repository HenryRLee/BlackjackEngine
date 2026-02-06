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

#include "AdvancedCalculator.h"
#include "UsedCard.h"

void AdvancedCalculator::InitiateCardCounts(UsedCard * usedcard)
{
	vector <Card> vCard;

	vInitialCount.resize(13);

	for (int i=2; i<=11; i++)
	{
		vInitialCount[i] = 4 * iDeckNumber;
	}

	/* iCount[0] marks the total counts */
	vInitialCount[0] = 52 * iDeckNumber;
	vInitialCount[10] = 16 * iDeckNumber;

	if (usedcard != NULL)
	{
		vCard = usedcard->ShowCards();

		for (int i=0; i<vCard.size(); i++)
		{
			int value;
			value = vCard[i].GetValue();

			vInitialCount[value]--;
			vInitialCount[0]--;
		}
	}
}

double AdvancedCalculator::ProbOfGettingCard(int value, vector <int> vRemaining)
{
	double prob;
	
	if (value < vRemaining.size())
	{
		prob = (double)vRemaining[value]/(double)vRemaining[0];
	}
	else
	{
		cout << "Error when calcualting ProbOfGettingCard" << endl;
	}

	return prob;
}

double AdvancedCalculator::ProbOfGettingCard(int value)
{
	double prob;

	if (value <= 11)
	{
		prob = (double)vInitialCount[value]/(double)vInitialCount[0];
	}

	return prob;
}

vector <int> AdvancedCalculator::CardFlowing(int value, vector <int> vRemaining)
{
	vector <int> vCurrent(vRemaining);

	if (value < vCurrent.size())
	{
		if (vCurrent[value] >= 0)
		{
			vCurrent[value]--;
			vCurrent[0]--;
		}
	}
	else
	{
		cout << "Error when calcualting CardFlowing" << endl;
	}

	return vCurrent;
}

ProbSet AdvancedCalculator::ProbOfHandsDealerFirstTurn(HandScore handPlayer, 
		HandScore handDealer, vector <int> vRemaining)
{
	ProbSet pbCurrent;

	/* If Dealer Score is upto 11, skip Blackjack checking. */
	if (handDealer.iScore > 11)
	{
		if (handPlayer.iScore > 21)
		{
			pbCurrent.dEV = -1;
			return pbCurrent;
		}
		else
		{
			return ProbOfHandsDealerTurn(handPlayer, handDealer, vRemaining);
		}
	}

	for (int i=2; i<=11; i++)
	{
		ProbSet pbNew;
		HandScore handCurrent;
		vector <int> vCurrent(vRemaining);

		vCurrent = CardFlowing(i, vCurrent);
		if (((handDealer.iScore == 10) && (i == 11)) ||
				((handDealer.iScore == 11) && (handDealer.bSoft) && (i == 10)))
		{
			/* Dealer has a Blackjack */
			if ((bSOBO) && (iAdditionalHand > 0))
			{
				pbNew.dEV = 0;
			}
			else
			{
				pbNew.dEV = -1;
			}

			if (bDoubled && bDOBO)
			{
				if (!bSOBO || (iAdditionalHand == 0))
				{
					pbNew.dEV = -0.5;
				}
			}

			pbCurrent = ProbAfterGettingCard(pbCurrent, pbNew, i, vRemaining);
		}
		else if (handPlayer.iScore > 21)
		{
			pbNew.dEV = -1;
			pbCurrent = ProbAfterGettingCard(pbCurrent, pbNew, i, vRemaining);
		}

		else
		{
			handCurrent = GetOneCard(handDealer, i);
			pbNew = ProbOfHandsDealerTurn(handPlayer, handCurrent, vCurrent);

			pbCurrent = ProbAfterGettingCard(pbCurrent, pbNew, i, vRemaining);
		}
	}

	return pbCurrent;
}

ProbSet AdvancedCalculator::ProbOfHandsDealerTurn(HandScore handPlayer, 
		HandScore handDealer, vector <int> vRemaining)
{
	ProbSet pbCurrent;

	if (DealerHits(handDealer))
	{
		for (int i=2; i<=11; i++)
		{
			ProbSet pbNew;
			HandScore handCurrent;
			vector <int> vCurrent(vRemaining);

			vCurrent = CardFlowing(i, vCurrent);
			handCurrent = GetOneCard(handDealer, i);
			pbNew = ProbOfHandsDealerTurn(handPlayer, handCurrent, vCurrent);

			pbCurrent = ProbAfterGettingCard(pbCurrent, pbNew, i, vRemaining);
		}
	}
	else
	{
		if (handDealer.iScore > 21)
			pbCurrent.dEV = 1;
		else if (handDealer.iScore < handPlayer.iScore)
			pbCurrent.dEV = 1;
		else if (handDealer.iScore == handPlayer.iScore)
			pbCurrent.dEV = 0;
		else if (handDealer.iScore > handPlayer.iScore)
			pbCurrent.dEV = -1;
	}

	return pbCurrent;
}

ProbSet AdvancedCalculator::ProbOfHandsPlayerTurn(HandScore handPlayer, 
		HandScore handDealer, vector <int> vRemaining, int action)
{
	ProbSet pbHit;
	ProbSet pbStand;

	/* Bust */
	if (handPlayer.iScore > 21)
	{
		return ProbOfHandsDealerFirstTurn(handPlayer, handDealer, vRemaining);
	}

	if ((handPlayer.iScore == 21) && (!handPlayer.bSoft))
	{
		/* Whatever, it busts */
		if (action == HIT)
		{
			handPlayer.iScore = 22;

			return ProbOfHandsDealerFirstTurn(handPlayer, handDealer,
					vRemaining);
		}
	}

	/* Hit */
	if ((action == HIT) || (action == NONE))
	{
		ProbSet pbNew;

		for (int i=2; i<=11; i++)
		{
			HandScore handCurrent;
			vector <int> vCurrent(vRemaining);

			vCurrent = CardFlowing(i, vCurrent);
			handCurrent = GetOneCard(handPlayer, i);
			pbNew = ProbOfHandsPlayerTurn(handCurrent, handDealer, vCurrent);

			pbHit = ProbAfterGettingCard(pbHit, pbNew, i, vRemaining);
		}
	}
	/* Hit */

	/* Stand */
	if ((action == STAND) || (action == NONE))
	{
		pbStand = ProbOfHandsDealerFirstTurn(handPlayer, handDealer,
				vRemaining);
	}
	/* Stand */
	if (action == NONE)
	{
		if (pbHit.dEV > pbStand.dEV)
			return pbHit;
		else
			return pbStand;
	}
	else if (action == HIT)
	{
		return pbHit;
	}
	else if (action == STAND)
	{
		return pbStand;
	}
	
	return pbStand;
}

ProbSet AdvancedCalculator::ProbOfHandsPlayerHit(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbHit;
	vector <int> vStart(vInitialCount);

	pbHit = ProbOfHandsPlayerTurn(handPlayer, handDealer, vStart, HIT);

	return pbHit;
}

ProbSet AdvancedCalculator::ProbOfHandsPlayerStand(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbStand;
	vector <int> vStart(vInitialCount);

	pbStand = ProbOfHandsPlayerTurn(handPlayer, handDealer, vStart, STAND);

	return pbStand;
}

ProbSet AdvancedCalculator::ProbOfHandsPlayerHitOrStand(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbCurrent;
	vector <int> vStart(vInitialCount);

	pbCurrent = ProbOfHandsPlayerTurn(handPlayer, handDealer, vStart);

	return pbCurrent;
}

ProbSet AdvancedCalculator::ProbOfHandsPlayerDouble(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbDouble;
	ProbSet pbNew;

	bDoubled = true;

	for (int i=2; i<=11; i++)
	{
		HandScore handCurrent;
		vector <int> vStart(vInitialCount);

		vStart = CardFlowing(i, vStart);
		handCurrent = GetOneCard(handPlayer, i);
		pbNew = ProbOfHandsPlayerTurn(handCurrent, handDealer, vStart, STAND);

		pbDouble = ProbAfterGettingCard(pbDouble, pbNew, i, vInitialCount);
	}

	bDoubled = false;
	pbDouble.dEV *= 2;

	return pbDouble;
}

ProbSet AdvancedCalculator::ProbAfterGettingCard(ProbSet pbCurrent, 
		ProbSet pbNextCard, int iCardValue, vector <int> vRemaining)
{
	pbCurrent.dEV += ProbOfGettingCard(iCardValue, vRemaining)
		* pbNextCard.dEV;

	return pbCurrent;
}

void AdvancedCalculator::ShowProbSetByAction(int iPlayerScore, bool bPlayerSoft,
		int iDealerScore, bool bDealerSoft, int action, UsedCard * usedcard)
{
	InitiateCardCounts(usedcard);
	SimpleCalculator::ShowProbSetByAction(iPlayerScore, bPlayerSoft, 
			iDealerScore, bDealerSoft, action, usedcard);
}

void AdvancedCalculator::ShowProbSetByNextCard(int iPlayerScore, 
		bool bPlayerSoft, int iDealerScore, bool bDealerSoft, int action,
		UsedCard * usedcard)
{
	InitiateCardCounts(usedcard);
	SimpleCalculator::ShowProbSetByNextCard(iPlayerScore, bPlayerSoft, 
			iDealerScore, bDealerSoft, action, usedcard);
}

void AdvancedCalculator::ShowDeltaOfEachTakenCard(int iPlayerScore,
		bool bPlayerSoft, int iDealerScore, bool bDealerSoft,
		int iFirstAction, int iSecondAction, UsedCard * usedcard)
{
	HandScore handPlayer;
	HandScore handDealer;
	double delta[12];
	double deltadelta[12];
	ProbSet pbFirst;
	ProbSet pbSecond;

	handPlayer.iScore = iPlayerScore;
	handPlayer.bSoft = bPlayerSoft;
	handDealer.iScore = iDealerScore;
	handDealer.bSoft = bDealerSoft;

	UsedCard vUsedCard = *usedcard;
	InitiateCardCounts(&vUsedCard);

	pbFirst = ProbOfHandsPlayerAction(handPlayer, handDealer,
			iFirstAction);
	pbSecond = ProbOfHandsPlayerAction(handPlayer, handDealer,
			iSecondAction);

	/* Original delta */
	delta[0] = pbFirst.dEV - pbSecond.dEV;

	for (int i=2; i<=11; i++)
	{
		UsedCard vRemaining = vUsedCard;
		vRemaining.GetOneCard(i);
		InitiateCardCounts(&vRemaining);

		pbFirst = ProbOfHandsPlayerAction(handPlayer, handDealer,
				iFirstAction);
		pbSecond = ProbOfHandsPlayerAction(handPlayer, handDealer,
				iSecondAction);

		delta[i] = pbFirst.dEV - pbSecond.dEV;
		deltadelta[i] = delta[i] - delta[0];
	}

	cout << fixed;

	cout << "Original Delta " << delta[0] << endl;
	
	for (int i=2; i<=11; i++)
	{
		cout << "Value " << i << " \tDelta " << delta[i];
		cout << "\tDelta of Delta " << deltadelta[i] << endl;
	}
}


AdvancedCalculator::AdvancedCalculator(void)
{
}

AdvancedCalculator::~AdvancedCalculator(void)
{
}
