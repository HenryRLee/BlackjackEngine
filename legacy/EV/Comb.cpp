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

/*
 * The function Comb calculates the number of combinations of reaching an
 * integer num by adding integers from the set {1 2 .. choices}.
 * For example, to count the possible combinations of cards used from 16 to
 * 21, we can let num be 5 and choices be 10. The result is 7.
 * All combinations in this example are listed below.
 *    A 2 3 4 5 6 7 8 9 T
 *    5 0 0 0 0 0 0 0 0 0
 *    3 1 0 0 0 0 0 0 0 0
 *    1 2 0 0 0 0 0 0 0 0
 *    2 0 1 0 0 0 0 0 0 0
 *    0 1 1 0 0 0 0 0 0 0
 *    1 0 0 1 0 0 0 0 0 0
 *    0 0 0 0 1 0 0 0 0 0
 *
 * Another function Comb2Groups calculates the number of combinations of
 * reaching two integers numX and numY.
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

int Comb(int num, int choices, vector <int> result)
{
	int sum = 0;

	if ((num == 1) || (num == 0) || (choices == 1))
	{
		if (num >= 1)
			result[0] += num;

		for (int i=0; i<result.size(); i++)
			cout << result[i] << " ";

		cout << endl;

		return 1;
	}
	else
	{
		for (int i=num; i>0; i--)
		{
			vector <int> domestic = result;

			if (i > choices)
				continue;

			domestic[i-1]++;

			sum += Comb(num-i, i, domestic);
		}
		return sum;
	}
}

int Comb2Groups(int numX, int numY, int choices, vector <int> result)
{
	int sum = 0;

	if ((((numX == 1) || (numX == 0)) && ((numY == 1) || (numY == 0))) ||
			(choices == 1))
	{
		if (numX >= 1)
			result[0] += numX;
		if (numY >= 1)
			result[0] += numY;

		for (int i=0; i<result.size(); i++)
			cout << result[i] << " ";

		cout << endl;


		return 1;
	}
	else
	{
		int numL;
		int numS;

		if (numX >= numY)
		{
			numL = numX;
			numS = numY;
		}
		else
		{
			numL = numY;
			numS = numX;
		}

		for (int i=numL; i>0; i--)
		{
			vector <int> domestic = result;

			if (i > choices)
				continue;

			domestic[i-1]++;

			if (numS >= i)
				sum += Comb2Groups(numS-i, numL, i, domestic);
			else if (numL >= i)
				sum += Comb2Groups(numL-i, numS, i, domestic);
		}

		return sum;
	}
}

int main(int argc, char *argv[])
{
	int sum;

	if (argc >= 3)
	{
		vector <int> result(10, 0);

		cout << "A 2 3 4 5 6 7 8 9 T" << endl;
		sum = Comb2Groups(atoi(argv[1]), atoi(argv[2]), 10, result);
		//sum = Comb(atoi(argv[1]), 10, result);
		cout << sum << endl;
	}

	return 0;
}
