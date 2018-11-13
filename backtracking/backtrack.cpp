#include "backtrack.hpp"
#include "priorityqueue.hpp"

Backtrack::Backtrack()
{
	n = w = p = W = maxprofit = numbest = 0;
	include = bestset = nullptr;
	items = nullptr;
}

bool
Backtrack::promising(std::uint64_t i)
{
	std::uint64_t j, k, totweight;
	float bound;

	j = k = totweight = 0;
	bound = 0.0;
	
	if(items[i].weight >= W)
		return false;
	else
	{
		j = i + 1;
		bound = items[i].profit;
		totweight = items[i].weight;
		while(j <= n && totweight + items[j].weight <= W)
		{
			totweight += items[j].weight;
			bound += items[j].profit;
			j++;
		}
		k = j;
		if(k <= n)
			bound += (W - totweight) * items[k].profit 
									 / items[k].weight;
		return bound > maxprofit;
	}
}

void
Backtrack::knapsack(std::uint64_t i)
{
	if(items[i].weight <= W && items[i].profit > maxprofit)
	{
		maxprofit = items[i].profit;
		numbest = i;
		bestset = include;
	}
	if(promising(i))
	{
		//include[i + 1] = "yes";
		include[i + 1] = &YES;
		knapsack(i + 1);
		//include[i + 1] = "no";
		include[i + 1] = &NO;
		knapsack(i + 1);
	}
}

bool
Backtrack::setW(std::uint64_t w)
{
	if(W - w < 0)
		return false;
	W -= w;
	return true;
}

void
Backtrack::setn(std::uint64_t n)
{
	this->n = n;
}

std::uint64_t
Backtrack::getW()
{
	return W;
}

std::uint64_t
Backtrack::getn()
{
	return n;
}

void
Backtrack::enqueue(item* i)
{
	pq.enqueue(i);
}

itemptr&
Backtrack::top()
{
	return pq.top();
}