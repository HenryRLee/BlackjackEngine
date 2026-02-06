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

namespace GameTerm
{
	enum Action
	{
		STAND, HIT, DOUBLE, SPLIT, SURRENDER
	};

	enum Status
	{
		NONE, WON, LOST, PUSH, BJ, WAITING, BUSTED, SURRENDERED, DOUBLEDWAITING
	};

	enum
	{
		MaxTimesSplitted = 7,
		MaxHands= 8,
		MaxScore = 21
	};
};

