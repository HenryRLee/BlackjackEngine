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

#include "SydneySimulation.h"
#include "ContinuousShufflingMachine.h"
#include "ManipulatedCardSequence.h"
#include "PenetrationShuffler.h"

SydneySimulation::SydneySimulation(void)
{
	shuffler = new PenetrationShuffler(8);
//	shuffler = new ContinuousShufflingMachine(6);
//	shuffler = new ManipulatedCardSequence;

	shuffler->SetPenetration(0.375);

	bHitOnSoft17 = false;
	bDouble = true;
	bSurrender = false;
	bSplit = true;
	bDealerTakesHole = false;
	bDealerPeaksHole = false;
	bDealerPeaksHoleOnAce = false;
	bDealerPeaksHoleOnTen = false;
	bHitAfterSplit = true;
	bDoubleAfterSplit = true;
	bDoubleOnAnyTwo = false;
	bDoubleOnNine = true;
	bDoubleOnTen = true;
	bDoubleOnEleven = true;
	bSplitAfterSplit = false;
	bResplitAces = false;
	bStandAfterSplittedAces = true;
	bLateSurrender = false;
	bSurrenderVsDealerAce = false;
	iTimesSplittedAllow = 1;
	dBlackJackPays = 2.5;
	bDOBO = true;
	bSOBO = true;
}

SydneySimulation::~SydneySimulation(void)
{
}
