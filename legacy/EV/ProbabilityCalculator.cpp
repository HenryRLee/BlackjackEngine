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

#include "ProbabilityCalculator.h"

void ProbabilityCalculator::ShowDeltaOfEachTakenCard(int iPlayerScore,
		bool bPlayerSoft, int iDealerScore, bool bDealerSoft,
		int iFirstAction, int iSecondAction, UsedCard * usedcard)
{
}

ProbabilityCalculator::ProbabilityCalculator(void)
{
	iMaxTimesSplitted = 1;
	bResplitAces = false;
	bHitOnSoft17 = false;
	bDOBO = true;
	bSOBO = false;
	iDeckNumber = 6;
	bDoubleOnAnyTwo = false;
	bDoubleOnSoft = false;
	bDoubleOnNine = true;
	bDoubleOnTen = true;
	bDoubleOnEleven = true;
	bStandAfterSplittedAces = true;
}

ProbabilityCalculator::~ProbabilityCalculator(void)
{
}
