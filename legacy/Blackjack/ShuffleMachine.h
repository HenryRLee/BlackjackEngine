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
#include "Blackjack.h"
#include "Deck.h"
#include "Table.h"

class ShuffleMachine
{
protected:
	int iDeckNumber;
	int iTotalCardNumber;
	float fPenetration;

public:
	int SetDeckNumber(int num);
	void SetPenetration(float penetration);

	virtual Card PopOneCard(void) = 0;
	virtual Card PopOneCard(Table *) = 0;
	virtual void ShuffleCards(void) = 0;
	virtual void ShuffleCards(Table *) = 0;
	virtual void TakeSpecificCard(int value, int num = 1) = 0;

	ShuffleMachine(void);
	virtual ~ShuffleMachine(void);
};
