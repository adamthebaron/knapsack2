#include "backtrack.hpp"

Backtrack::Backtrack()
{
	root = pos = nullptr;
	W = curw = maxp = 0;
}

bool
Backtrack::promising(std::uint64_t i)
{
	std::uint64_t j, k, totweight;
	float bound;
	
	j = k = totweight = 0;
	bound = 0.0;
	
	if(curw >= W)
	{
		return false;
	}
	else
	{
		j = i + 1;
		bound = profits[i];
		totweight = weights[i];
		while(j <= n && totweight + weights[j] <= W)
		{
			totweight += weights[j];
			bound += profits[j];
			j++;
		}
		k = j;
		if(k <= n)
		{
			bound += (W - totweight) * profits[k] / weights[k];
		}
		return bound > maxp;
	}
}

void
Backtrack::knapsack(std::uint64_t i)
{
	std::uint64_t numbest;
	std::string* include;

	if(weights[i] <= W && profits[i] > maxp)
	{
		maxp = profits[i];
		numbest = i;
		bestset = include;
	}
	if((promising(i))
	{
		include[i + 1] = "yes";
		knapsack(i + 1);
		include[i + 1] = "no";
		knapsack(i + 1);
	}
}