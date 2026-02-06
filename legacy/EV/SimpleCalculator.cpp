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

#include "SimpleCalculator.h"

double SimpleCalculator::ProbOfGettingCard(int value)
{
	double prob;

	if (value == 10)
		prob = double(4)/double(13);
	else
		prob = double(1)/double(13);

	return prob;
}

bool SimpleCalculator::DealerHits(HandScore hand)
{
	if (hand.iScore < 17)
		return true;
	else
		return false;

	if (hand.iScore < 17)
	{
		return true;
	}
	else if (hand.iScore > 17)
	{
		return false;
	}
	else if (hand.iScore == 17)
	{
		if (!hand.bSoft)
		{
			return false;
		}
		else
		{
			if (bHitOnSoft17)
				return true;
			else
				return false;
		}
	}
}

HandScore SimpleCalculator::GetOneCard(HandScore hand, int iCardValue)
{
	int iNewScore;

	iNewScore = hand.iScore + iCardValue;

	if (iNewScore > 21)
	{
		if (iCardValue == 11)
		{
			iNewScore -= 10;
		}
		else if (hand.bSoft)
		{
			iNewScore -= 10;
			hand.bSoft = false;
		}
	}
	else if (iCardValue == 11)
	{
		hand.bSoft = true;
	}

	hand.iScore = iNewScore;

	return hand;
}

ProbSet SimpleCalculator::ProbOfHandsDealerFirstTurn(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbCurrent;

	if (handDealer.iScore > 11)
		return ProbOfHandsDealerTurn(handPlayer, handDealer);

	for (int i=2; i<=11; i++)
	{
		ProbSet pbNew;
		HandScore handCurrent;

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

			pbCurrent = ProbAfterGettingCard(pbCurrent, pbNew, i);
		}
		else if (handPlayer.iScore > 21)
		{
			pbNew.dEV = -1;
			pbCurrent = ProbAfterGettingCard(pbCurrent, pbNew, i);
		}
		else
		{
			handCurrent = GetOneCard(handDealer, i);
			pbNew = ProbOfHandsDealerTurn(handPlayer, handCurrent);

			pbCurrent = ProbAfterGettingCard(pbCurrent, pbNew, i);
		}
	}

	return pbCurrent;
}

ProbSet SimpleCalculator::ProbOfHandsDealerTurn(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbCurrent;

	if (DealerHits(handDealer))
	{
		for (int i=2; i<=11; i++)
		{
			ProbSet pbNew;
			HandScore handCurrent;

			handCurrent = GetOneCard(handDealer, i);
			pbNew = ProbOfHandsDealerTurn(handPlayer, handCurrent);

			pbCurrent = ProbAfterGettingCard(pbCurrent, pbNew, i);
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

ProbSet SimpleCalculator::ProbOfHandsPlayerTurn(HandScore handPlayer, 
		HandScore handDealer, int action)
{
	ProbSet pbHit;
	ProbSet pbStand;

	/* Bust */
	if (handPlayer.iScore > 21)
	{
		return ProbOfHandsDealerFirstTurn(handPlayer, handDealer);
	}

	if ((handPlayer.iScore == 21) && (!handPlayer.bSoft))
	{
		/* Whatever, it busts */
		if (action == HIT)
		{
			handPlayer.iScore = 22;

			return ProbOfHandsDealerFirstTurn(handPlayer, handDealer);
		}
	}
	/* Hit */
	if ((action == HIT) || (action == NONE))
	{
		ProbSet pbNew;

		for (int i=2; i<=11; i++)
		{
			HandScore handCurrent;

			handCurrent = GetOneCard(handPlayer, i);
			pbNew = ProbOfHandsPlayerTurn(handCurrent, handDealer);

			pbHit = ProbAfterGettingCard(pbHit, pbNew, i);
		}
	}
	/* Hit */

	/* Stand */
	if ((action == STAND) || (action == NONE))
	{
		pbStand = ProbOfHandsDealerFirstTurn(handPlayer, handDealer);
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

ProbSet SimpleCalculator::ProbOfHandsPlayerHit(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbHit;

	pbHit = ProbOfHandsPlayerTurn(handPlayer, handDealer, HIT);

	return pbHit;
}

ProbSet SimpleCalculator::ProbOfHandsPlayerStand(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbStand;

	pbStand = ProbOfHandsPlayerTurn(handPlayer, handDealer, STAND);

	return pbStand;
}

ProbSet SimpleCalculator::ProbOfHandsPlayerHitOrStand(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbCurrent;

	pbCurrent = ProbOfHandsPlayerTurn(handPlayer, handDealer);

	return pbCurrent;
}

ProbSet SimpleCalculator::ProbOfHandsPlayerDouble(HandScore handPlayer, 
		HandScore handDealer)
{
	ProbSet pbDouble;
	ProbSet pbNew;

	bDoubled = true;

	for (int i=2; i<=11; i++)
	{
		HandScore handCurrent;

		handCurrent = GetOneCard(handPlayer, i);
		pbNew = ProbOfHandsPlayerTurn(handCurrent, handDealer, STAND);

		pbDouble = ProbAfterGettingCard(pbDouble, pbNew, i);
	}

	bDoubled = false;
	pbDouble.dEV *= 2;

	return pbDouble;
}

ProbSet SimpleCalculator::ProbOfHandsPlayerSplit(HandScore handPlayer, 
		HandScore handDealer, int iTimesSplitted)
{
	ProbSet pbCurrent;
	ProbSet pbSplit;
	ProbSet pbHS;
	ProbSet pbDouble;

	iTimesSplitted++;

	for (int round=0; round<2; round++)
	{
		for (int i=2; i<=11; i++)
		{
			HandScore handCurrent;
			bool bSplitted = false;

			handCurrent = GetOneCard(handPlayer, i);

			if (!(bStandAfterSplittedAces && (handPlayer.iScore == 11)))
			{
				/* General rules for hit or stand */
				pbHS = ProbOfHandsPlayerHitOrStand(handCurrent, handDealer);
			}
			else
			{
				/* Special rule that no hitting after splitting Aces */
				pbHS = ProbOfHandsPlayerStand(handCurrent, handDealer);
			}

			if (bDoubleOnAnyTwo)
			{
				/* Double allowed on any two cards */
				pbDouble = ProbOfHandsPlayerDouble(handCurrent, handDealer);
			}
			else
			{
				/* Special doubling rules */
				if (!bDoubleOnSoft && handCurrent.bSoft)
					pbDouble.dEV = -100;
				else if (bDoubleOnNine && (handCurrent.iScore == 9))
					pbDouble = ProbOfHandsPlayerDouble(handCurrent, handDealer);
				else if (bDoubleOnTen && (handCurrent.iScore == 10))
					pbDouble = ProbOfHandsPlayerDouble(handCurrent, handDealer);
				else if (bDoubleOnEleven && (handCurrent.iScore == 11))
					pbDouble = ProbOfHandsPlayerDouble(handCurrent, handDealer);
				else
					pbDouble.dEV = -100;
			}

			if (i == handPlayer.iScore)
			{
				if (iTimesSplitted < iMaxTimesSplitted)
				{
					if (bResplitAces || (i!=11))
					{
						pbSplit = ProbOfHandsPlayerSplit(handPlayer, handDealer,
								iTimesSplitted);
						bSplitted = true;
					}
				}
			}

			if (bSplitted)
			{
				if ((pbHS.dEV>=pbSplit.dEV) && (pbHS.dEV>=pbDouble.dEV))
				{
					pbCurrent = ProbAfterGettingCard(pbCurrent, pbHS, i);
				}
				else if ((pbSplit.dEV>=pbHS.dEV) && (pbSplit.dEV>=pbDouble.dEV))
				{
					pbCurrent = ProbAfterGettingCard(pbCurrent, pbSplit, i);
				}
				else if ((pbDouble.dEV>=pbHS.dEV) && (pbDouble.dEV>=pbSplit.dEV))
				{
					pbCurrent = ProbAfterGettingCard(pbCurrent, pbDouble, i);
				}
				else
				{
					cout << "Error in Calculating splitting." << endl;
				}
			}
			else
			{
				if (pbHS.dEV > pbDouble.dEV)
				{
					pbCurrent = ProbAfterGettingCard(pbCurrent, pbHS, i);
				}
				else
				{
					pbCurrent = ProbAfterGettingCard(pbCurrent, pbDouble, i);
				}
			}
		}

		if (round == 0)
			iAdditionalHand++;
		else
			iAdditionalHand--;
	}

	return pbCurrent;
}

ProbSet SimpleCalculator::ProbOfHandsPlayerAction(HandScore player,
		HandScore dealer, int action)
{
	ProbSet pbSet;

	switch (action)
	{
	case HIT:
		pbSet = ProbOfHandsPlayerHit(player, dealer);
		break;
	case STAND:
		pbSet = ProbOfHandsPlayerStand(player, dealer);
		break;
	case SPLIT:
		pbSet = ProbOfHandsPlayerSplit(player, dealer, 0);
		break;
	case DOUBLE:
		pbSet = ProbOfHandsPlayerDouble(player, dealer);
		break;
	case SURRENDER:
		pbSet.dEV = -0.5;
		break;
	default:
		break;
	}

	return pbSet;
}

ProbSet SimpleCalculator::ProbAfterGettingCard(ProbSet pbCurrent, 
		ProbSet pbNextCard, int iCardValue)
{
	pbCurrent.dEV += ProbOfGettingCard(iCardValue) * pbNextCard.dEV;

	return pbCurrent;
}

void SimpleCalculator::ShowProbSetByAction(int iPlayerScore, bool bPlayerSoft, 
		int iDealerScore, bool bDealerSoft, int action, UsedCard *)
{
	ProbSet pbHit;
	ProbSet pbStand;
	ProbSet pbDouble;
	ProbSet pbSplit;
	HandScore handPlayer;
	HandScore handDealer;

	handPlayer.iScore = iPlayerScore;
	handPlayer.bSoft = bPlayerSoft;
	handDealer.iScore = iDealerScore;
	handDealer.bSoft = bDealerSoft;

	pbHit = ProbOfHandsPlayerHit(handPlayer, handDealer);

	cout << fixed;
	cout << "Hit: " << endl;
	cout << "EV " << pbHit.dEV << endl;
	cout << endl;

	pbStand = ProbOfHandsPlayerStand(handPlayer, handDealer);

	cout << "Stand: " << endl;
	cout << "EV " << pbStand.dEV << endl;
	cout << endl;

	if ((action & ALLOWDOUBLE) == ALLOWDOUBLE)
	{
		pbDouble = ProbOfHandsPlayerDouble(handPlayer, handDealer);

		cout << "Double: " << endl;
		cout << "EV " << pbDouble.dEV << endl;
		cout << endl;
	}

	if ((action & ALLOWSPLIT) == ALLOWSPLIT)
	{
		if ((iPlayerScore >= 4) && (iPlayerScore%2 == 0) && 
				(!bPlayerSoft || (iPlayerScore == 12)))
		{
			handPlayer.iScore = iPlayerScore/2;
			if ((iPlayerScore == 12) && (bPlayerSoft))
				handPlayer.iScore = 11;

			handPlayer.bSoft = bPlayerSoft;

			pbSplit = ProbOfHandsPlayerSplit(handPlayer, handDealer, 0);
			cout << "Split: " << endl;
			cout << "EV " << pbSplit.dEV << endl;
		}
	}
}

void SimpleCalculator::ShowProbSetByNextCard(int iPlayerScore, bool bPlayerSoft,	int iDealerScore, bool bDealerSoft, int action, UsedCard *)
{
	ProbSet pbHit;
	ProbSet pbStand;
	ProbSet pbHitTotal;
	ProbSet pbStandTotal;
	HandScore handPlayer;
	HandScore handDealer;

	handPlayer.iScore = iPlayerScore;
	handPlayer.bSoft = bPlayerSoft;
	handDealer.iScore = iDealerScore;
	handDealer.bSoft = bDealerSoft;

	cout << fixed;

	for (int i=2; i<=11; i++)
	{
		HandScore handCurrent;

		handCurrent = GetOneCard(handPlayer, i);
		pbHit = ProbOfHandsPlayerHitOrStand(handCurrent, handDealer);

		handCurrent = GetOneCard(handDealer, i);
		pbStand = ProbOfHandsPlayerStand(handPlayer, handCurrent);

		pbHitTotal.dEV += ProbOfGettingCard(i) * pbHit.dEV;
		pbStandTotal.dEV += ProbOfGettingCard(i) * pbStand.dEV;

		cout << "Hand " << i << "\tProb " << ProbOfGettingCard(i);
		cout << "\tHit " << pbHit.dEV << "\tStand " << pbStand.dEV;
		cout << endl;
	}

	cout << "Total\tHit " << pbHitTotal.dEV << "\tStand " << pbStandTotal.dEV;
	cout << "\tDifference " << (pbHitTotal.dEV-pbStandTotal.dEV);
	cout << endl;

}

SimpleCalculator::SimpleCalculator(void)
{
	bDoubled = false;
	iAdditionalHand = 0;
}

SimpleCalculator::~SimpleCalculator(void)
{
}
