/*
 * Martingale
 *
 * Player double his bet after every loss so that the first win would recover
 * all previous losses plus win a profit equal to the original stake.
 *
 * Let p be the probability of winning. If casino has no maximum bet limit,
 * the expectation of player profolio will be p. If casino has a maximum limit,
 * the expectation will be (1 - (1-p)^n * 2^n).
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	long long times = 1000*1000;
	long long minbet = 1;
	long long bet = minbet;
	long long budget = times * 100;
	int maxbet = 50;
	long long i;

	srand(time(NULL));

	for (i=0; i<times; i++)
	{
		if ((rand() % 10000) < 5016)
		{
			/* Win */
			budget += bet;
			bet = minbet;
		}
		else
		{
			/* Lose */
			if (bet > budget)
			{
				printf("Bankrupt! Round %lld, bet %lld\n", i, bet);
				break;
			}

			budget -= bet;
			bet = bet * 2;

			if (bet > maxbet)
			{
//				printf("Overflow max bet\n");
				bet = minbet;
			}
		}
	}

	printf("Budget %lld\n", budget);

	
	return 0;
}
