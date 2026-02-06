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

#pragma once
#include "UsedCard.h"
#include <iostream>
#include <vector>
using namespace std;

class ProbabilityCalculator
{
protected:
	bool bResplitAces;
	int iMaxTimesSplitted;
	bool bHitOnSoft17;
	bool bDOBO;
	bool bSOBO;
	bool bDoubleOnAnyTwo;
	bool bDoubleOnSoft;
	bool bDoubleOnNine;
	bool bDoubleOnTen;
	bool bDoubleOnEleven;
	bool bStandAfterSplittedAces;
	int iDeckNumber;

	enum PlayerAction
	{
		NONE, HIT, STAND, DOUBLE, SPLIT, SURRENDER,
	};

public:
	virtual void ShowProbSetByAction(int iPlayerScore, bool bPlayerSoft, 
			int iDealerScore, bool bDealerSoft, int action=0,
			UsedCard * usedcard=NULL) = 0;

	virtual void ShowProbSetByNextCard(int iPlayerScore, bool bPlayerSoft, 
			int iDealerScore, bool bDealerSoft, int action=0,
			UsedCard * usedcard=NULL) = 0;

	virtual void ShowDeltaOfEachTakenCard(int iPlayerScore, bool bPlayerSoft,
			int iDealerScore, bool bDealerSoft, int iFirstAction=HIT,
			int iSecondAction=STAND, UsedCard * usedcard=NULL);

	ProbabilityCalculator(void);
	~ProbabilityCalculator(void);
};

