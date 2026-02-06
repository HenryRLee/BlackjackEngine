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
#include "ShuffleMachine.h"

class ContinuousShufflingMachine :
	public ShuffleMachine
{
protected:
	vector <Card> vCard;
	vector <Card> vUsedCard;
	Deck deck;

public:
	Card PopOneCard(void);
	Card PopOneCard(Table *);

	void ShuffleCards(void);
	void ShuffleCards(Table *);
	void TakeSpecificCard(int value, int num = 1);

	ContinuousShufflingMachine(void);
	ContinuousShufflingMachine(int iDeckNumber);
	~ContinuousShufflingMachine(void);
};
