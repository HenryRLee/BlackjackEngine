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
#include "SimpleCalculator.h"

class StoredEv
{
public:
	double dEV;
	bool bMark;

	StoredEv(void)
	{
		dEV = 0;
		bMark = false;
	}
};

class SimpleFastCalculator :
	public SimpleCalculator
{
private:
	StoredEv sePlayer[22][22][2][2];
	StoredEv seDealer[22][22][2][2];

protected:
	ProbSet ProbOfHandsDealerTurn(HandScore player, HandScore dealer);

	ProbSet ProbOfHandsPlayerTurn(HandScore player, HandScore dealer, 
			int action=NONE);

public:
	SimpleFastCalculator(void);
	~SimpleFastCalculator(void);
};
