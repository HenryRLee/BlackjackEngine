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

#include "NoStrategy.h"
#include "Hand.h"
#include "Table.h"

void NoStrategy::OutputDialogue(bitset <5> allowSet)
{
	cout << "Input your Selection" << endl;
	cout << "Available options: ";

	if (allowSet[HIT] == 1)
		cout << "HIT ";
	if (allowSet[STAND] == 1)
		cout << "STAND ";
	if (allowSet[DOUBLE] == 1)
		cout << "DOUBLE ";
	if (allowSet[SPLIT] == 1)
		cout << "SPLIT ";
	if (allowSet[SURRENDER] == 1)
		cout << "SURRENDER ";
	cout << endl;
}

int NoStrategy::InputSelection(bitset <5> allowSet)
{
	string input;
	int action;

	cin >> input;

	if ((input.compare("HIT") && input.compare("Hit") && input.compare("H") &&
				input.compare("h") && input.compare("hit")) == 0) 
	{
		cout << "HIT" << endl;
		action = HIT;
	}
	else if ((input.compare("STAND") && input.compare("Stand") && 
				input.compare("S") && input.compare("s") && 
				input.compare("stand")) == 0) 
	{
		cout << "STAND" << endl;
		action = STAND;
	}
	else if ((input.compare("SPLIT") && input.compare("Split") && 
				input.compare("P") && input.compare("p") && 
				input.compare("split")) == 0) 
	{
		cout << "SPLIT" << endl;
		action = SPLIT;
	}
	else if ((input.compare("DOUBLE") && input.compare("Double") && 
				input.compare("D") && input.compare("d") && 
				input.compare("double")) == 0) 
	{
		cout << "DOUBLE" << endl;
		action = DOUBLE;
	}
	else if ((input.compare("SURRENDER") && input.compare("Surrender") && 
				input.compare("R") && input.compare("r") && 
				input.compare("surrender")) == 0) 
	{
		cout << "SURRENDER" << endl;
		action = SURRENDER;
	}
	else
	{
		cout << "Action not supported" << endl;
		return InputSelection(allowSet);
	}

	if (allowSet[action] == 0)
	{
		cout << "Action not available" << endl;
		return InputSelection(allowSet);
	}
	else
	{
		return action;
	}
}

int NoStrategy::MakeDecision(Hand handCurrent, bitset <5> allowSet, Table table)
{
	int action;

	OutputDialogue(allowSet);
	action = InputSelection(allowSet);

	return action;
}

NoStrategy::NoStrategy(void)
{
}

NoStrategy::~NoStrategy(void)
{
}
