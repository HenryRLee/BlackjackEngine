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
#include "AdvancedCalculator.h"

class HashItem;

class AdvancedFastCalculator :
	public AdvancedCalculator
{
protected:
public:
	AdvancedFastCalculator(void);
	~AdvancedFastCalculator(void);
};

class HashItem
{
protected:
	vector <int> vUsedCards;
	bool bPlayerTurn;
	int iPlayerScore;
	bool bPlayerSoft;
	int iDealerScore;
	bool bDealerSoft;

	bool bAdditional;
	bool bDoubled;

	double dEV;

public:
	void SetItems(vector <int> usedcard, bool playerturn, int playerscore,
			bool playersoft, int dealerscore, bool dealersoft,
			bool additional = false, bool doubled = false)
	{
		vUsedCards = usedcard;
		bPlayerTurn = playerturn;
		iPlayerScore = playerscore;
		bPlayerSoft = playersoft;
		iDealerScore = dealerscore;
		bDealerSoft = dealersoft;
		bAdditional = additional;
		bDoubled = doubled;
	}

	void SetEV(double ev)
	{
		dEV = ev;
	}

	bool operator == (const HashItem item) const;

	unsigned int HashValue(void);

	HashItem(void)
	{
	}
};
