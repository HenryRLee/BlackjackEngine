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

#include "Deck.h"

Deck::Deck(void)
{
	char cCardInitString[52][2][8] = {
		{"AinC", "11"}, {"AinD", "11"}, {"AinH", "11"}, {"AinS", "11"},
		{"2inC", "2"}, {"2inD", "2"}, {"2inH", "2"}, {"2inS", "2"},
		{"3inC", "3"}, {"3inD", "3"}, {"3inH", "3"}, {"3inS", "3"},
		{"4inC", "4"}, {"4inD", "4"}, {"4inH", "4"}, {"4inS", "4"},
		{"5inC", "5"}, {"5inD", "5"}, {"5inH", "5"}, {"5inS", "5"},
		{"6inC", "6"}, {"6inD", "6"}, {"6inH", "6"}, {"6inS", "6"},
		{"7inC", "7"}, {"7inD", "7"}, {"7inH", "7"}, {"7inS", "7"},
		{"8inC", "8"}, {"8inD", "8"}, {"8inH", "8"}, {"8inS", "8"},
		{"9inC", "9"}, {"9inD", "9"}, {"9inH", "9"}, {"9inS", "9"},
		{"10inC", "10"}, {"10inD", "10"}, {"10inH", "10"}, {"10inS", "10"},
		{"JinC", "10"}, {"JinD", "10"}, {"JinH", "10"}, {"JinS", "10"},
		{"QinC", "10"}, {"QinD", "10"}, {"QinH", "10"}, {"QinS", "10"},
		{"KinC", "10"}, {"KinD", "10"}, {"KinH", "10"}, {"KinS", "10"}
	};

	for (int i=0; i<CardNumInDeck; i++)
	{
		card[i] = new Card(i, atoi(cCardInitString[i][1]), cCardInitString[i][0]);
	}
}

Deck::~Deck(void)
{
	for (int i=0; i<CardNumInDeck; i++)
	{
		delete(card[i]);
	}
}
