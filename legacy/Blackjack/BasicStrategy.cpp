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

#include "BasicStrategy.h"
#include "Hand.h"
#include "Table.h"
#include "Dealer.h"

void BasicStrategy::CreateDefaultTables(void)
{
	int iDfltHardTable[PMAX][DMAX] =
	{
		/*	2	3	4 	5 	6 	7 	8 	9 	X 	A	*/
		{	H, 	H, 	H, 	H, 	H, 	H, 	H, 	H, 	H, 	H	},	/* 4 */ 
		{	H, 	H, 	H, 	H, 	H, 	H, 	H, 	H, 	H, 	H	},	/* 5 */ 
		{	H, 	H, 	H, 	H, 	H, 	H, 	H, 	H, 	H, 	H	},	/* 6 */
		{	H,	H,	H,	H,	H,	H,	H,	H,	H,	H	},	/* 7 */
		{	H,	H,	H,	H,	H,	H,	H,	H,	H,	H	},	/* 8 */
		{	H,	DH,	DH,	DH,	DH,	H,	H,	H,	H,	H	},	/* 9 */
		{	DH,	DH,	DH,	DH,	DH,	DH,	DH,	DH,	H,	H	},	/* 10 */
		{	DH,	DH,	DH,	DH,	DH,	DH,	DH,	DH,	DH,	H	},	/* 11 */
		{	H,	H,	S,	S,	S,	H,	H,	H,	H,	H	},	/* 12 */
		{	S,	S,	S,	S,	S,	H,	H,	H,	H,	H	},	/* 13 */
		{	S,	S,	S,	S,	S,	H,	H,	H,	RH,	H	},	/* 14 */
		{	S,	S,	S,	S,	S,	H,	H,	H,	RH,	H	},	/* 15 */
		{	S,	S,	S,	S,	S,	H,	H,	RH,	RH,	H	},	/* 16 */
		{	S,	S,	S,	S,	S,	S,	S,	S,	S,	S	},	/* 17 */
		{	S,	S,	S,	S,	S,	S,	S,	S,	S,	S	},	/* 18 */
		{	S,	S,	S,	S,	S,	S,	S,	S,	S,	S	},	/* 19 */
		{	S,	S,	S,	S,	S,	S,	S,	S,	S,	S	},	/* 20 */
		{	S,	S,	S,	S,	S,	S,	S,	S,	S,	S	},	/* 21 */
	};

	int iDfltSoftTable[PSMAX][DMAX] =
	{
		/*	2	3	4	5	6	7	8	9	X	A	*/
		{	H,	H,	H,	H,	H,	H,	H,	H,	H,	H	},	/* 12 */
		{	H,	H,	H,	DH,	DH,	H,	H,	H,	H,	H	},	/* 13 */
		{	H,	H,	H,	DH,	DH,	H,	H,	H,	H,	H	},	/* 14 */
		{	H,	H,	DH,	DH,	DH,	H,	H,	H,	H,	H	},	/* 15 */
		{	H,	H,	DH,	DH,	DH,	H,	H,	H,	H,	H	},	/* 16 */
		{	H,	DH,	DH,	DH,	DH,	H,	H,	H,	H,	H	},	/* 17 */
		{	S,	DS,	DS,	DS,	DS,	S,	S,	H,	H,	H	},	/* 18 */
		{	S,	S,	S,	S,	S,	S,	S,	S,	S,	S	},	/* 19 */
		{	S,	S,	S,	S,	S,	S,	S,	S,	S,	S	},	/* 20 */
		{	S,	S,	S,	S,	S,	S,	S,	S,	S,	S	},	/* 21 */
	};

	int iDfltPairTable[PPMAX][DMAX] =
	{
		/*	2	3	4	5	6	7	8	9	X	A	*/
		{	P,	P,	P,	P,	P,	P,	H,	H,	H,	H	},	/* 2,2 */
		{	P,	P,	P,	P,	P,	P,	H,	H,	H,	H	},	/* 3,3 */
		{	H,	H,	H,	P,	P,	H,	H,	H,	H,	H	},	/* 4,4 */
		{	DH,	DH,	DH,	DH,	DH,	DH,	DH,	DH,	H,	H	},	/* 5,5 */
		{	P,	P,	P,	P,	P,	H,	H,	H,	H,	H	},	/* 6,6 */
		{	P,	P,	P,	P,	P,	P,	H,	H,	RH,	H	},	/* 7,7 */
		{	P,	P,	P,	P,	P,	P,	P,	P,	RH,	P	},	/* 8,8 */
		{	P,	P,	P,	P,	P,	S,	P,	P,	S,	S	},	/* 9,9 */
		{	S,	S,	S,	S,	S,	S,	S,	S,	S,	S	},	/* X,X */
		{	P,	P,	P,	P,	P,	P,	P,	P,	P,	P	},	/* A,A */
	};

	for (int i=0; i<PMAX; i++)
	{
		for (int j=0; j<DMAX; j++)
		{
			iHardTable[i][j] = iDfltHardTable[i][j];
		}
	}

	for (int i=0; i<PSMAX; i++)
	{
		for (int j=0; j<DMAX; j++)
		{
			iSoftTable[i][j] = iDfltSoftTable[i][j];
		}
	}

	for (int i=0; i<PPMAX; i++)
	{
		for (int j=0; j<DMAX; j++)
		{
			iPairTable[i][j] = iDfltPairTable[i][j];
		}
	}
}

int BasicStrategy::MakeDecision(Hand hand, bitset <5> allowSet, 
		Table table)
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

	if (allowSet[SPLIT] == 1)
	{
		value = hand.vCard[0].GetValue();
		action = iPairTable[value-PPDIFF][iDealerFaceup-DDIFF];
	}
	else if (soft)
	{
		action = iSoftTable[value-PSDIFF][iDealerFaceup-DDIFF];
	}
	else
	{
		action = iHardTable[value-PDIFF][iDealerFaceup-DDIFF];
	}

	if (action == DH)
	{
		if (allowSet[DOUBLE] == 1)
			action = DOUBLE;
		else
			action = HIT;
	}
	else if (action == DS)
	{
		if (allowSet[DOUBLE] == 1)
			action = DOUBLE;
		else
			action = STAND;
	}
	else if (action == RH)
	{
		if (allowSet[SURRENDER] == 1)
			action = SURRENDER;
		else
			action = HIT;
	}
	else if (action == RS)
	{
		if (allowSet[SURRENDER] == 1)
			action = SURRENDER;
		else
			action = STAND;
	}

	if ((action == HIT) && (allowSet[HIT] ==0))
		action = STAND;

	return action;
}

BasicStrategy::BasicStrategy(void)
{
	CreateDefaultTables();
}

BasicStrategy::~BasicStrategy(void)
{
}
