#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <vector>

#define MAX 1e6
#define MIN -1e6

int getMax(std::vector<int > input)  // for Integer
{
	int maxInt = MIN;
	for (int i=0;i < input.size();i++)
	{
		if (input[i] > maxInt)
		{
			maxInt = input[i];
		}
	}

	return maxInt;
}

int getMin(std::vector<int > input)  // for Integer
{
	int minInt = MAX;
	for (int i=0;i < input.size();i++)
	{
		if (input[i] < minInt)
		{
			minInt = input[i];
		}
	}

	return minInt;
}

int countNumber(std::vector<int > input, int x)
{
	int number = 0;
	for (int i=0;i<input.size();i++)
	{
		if (input[i] == x)
			number ++;		
	}
	return number;
}






#endif