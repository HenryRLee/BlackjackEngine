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
#include "Strategy.h"

class BasicStrategy :
	public Strategy
{
protected:
	enum Action
	{
		H = HIT, S = STAND, P = SPLIT, D = DOUBLE, R = SURRENDER,
		RH = R*10+H, RS = R*10+S, DH = D*10+H, DS = D*10+S
	};

	enum DealerFaceUp
	{
		D2 = 0, D3, D4, D5, D6, D7, D8, D9, D10, DA, DMAX
	};

	enum PlayerHard
	{
		P4 = 0, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18,
		P19, P20, P21, PMAX
	};

	enum PlayerSoft
	{
		PS12 = 0, PS13, PS14, PS15, PS16, PS17, PS18, PS19, PS20, PS21, PSMAX
	};

	enum PlayerPair
	{
		PP2 = 0, PP3, PP4, PP5, PP6, PP7, PP8, PP9, PP10, PPA, PPMAX
	};

	enum Difference
	{
		DDIFF = 2, PDIFF = 4, PSDIFF = 12, PPDIFF = 2
	};

	int iHardTable[PMAX][DMAX];
	int iSoftTable[PSMAX][DMAX];
	int iPairTable[PPMAX][DMAX];

	void CreateDefaultTables(void);

public:
	int MakeDecision(Hand handCurrent, bitset <5> allowSet, Table table);

	BasicStrategy(void);
	~BasicStrategy(void);
};
