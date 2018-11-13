#include "backtrack.hpp"
#include "priorityqueue.hpp"

Backtrack::Backtrack()
{
	n = w = p = W = maxprofit = numbest = 0;
	include = bestset = nullptr;
	items = nullptr;
}

bool
Backtrack::promising(std::uint64_t& i, std::uint64_t& profit, 
									   std::uint64_t& weight)
{
	std::uint64_t j, k, totweight;
	float bound;

	j = k = totweight = 0;
	bound = 0.0;
	//std::cout << "bound 1: " << bound << std::endl;

	if(weight >= W)
		return false;
	else
	{
		j = i + 1;
		bound = profit;
		//std::cout << "bound 2: " << bound << std::endl;
		totweight = weight;
		while(j < n && totweight + items[j].weight <= W)
		{
			totweight += items[j].weight;
			//std::cout << "bound 3: " << bound << std::endl;
			bound += items[j].profit;
			j++;
		}
		k = j;
		if(k < n)
		{
			bound += (float) ((W - totweight) * items[k].profit 
											  / items[k].weight);
			//std::cout << "bound 4: " << bound << std::endl;
		}
		std::cout << "(promising) at index " << i << " with bound " << bound << " and maxprofit " << maxprofit << std::endl;
		return bound > maxprofit;
	}
}

void
Backtrack::knapsack(std::uint64_t& i, std::uint64_t& profit, 
									  std::uint64_t& weight)
{
	if(weight <= W && profit > maxprofit)
	{
		maxprofit = profit;
		numbest = i;
		bestset = include;
	}
	if(promising(i, profit, weight) && i + 1 < n)
	{
		include[i + 1] = true;
		std::cout << "adding item " << i + 1 << std::endl;
		i++;
		profit += items[i + 1].profit;
		weight += items[i + 1].weight;
		knapsack(i, profit, weight);
		include[i + 1] = false;
		std::cout << "not adding item " << i + 1 << std::endl;
		i++;
		knapsack(i, profit, weight);
	}
}

bool
Backtrack::setW(std::uint64_t w)
{
	this->W = w;
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