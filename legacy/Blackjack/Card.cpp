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

#include "Card.h"

unsigned int Card::GetValue(void)
{
	return value;
}

string Card::ShowName(void)
{
	return name;
}

Card::Card(void)
{
}

Card::Card(int id, int value, char name[])
{
	this->id = id;
	this->value = value;
	this->name.assign(name);
}

Card::~Card(void)
{
}
