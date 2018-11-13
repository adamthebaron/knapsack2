#include <fstream>
#include <vector>

#include "priorityqueue.hpp"

std::uint64_t* w;
std::uint64_t* p;
std::uint64_t n, W, numbest, solweight, maxprofit;
std::vector<std::string> names;
char* include;
char* bestset;

bool
promising(std::uint64_t i, std::uint64_t profit, std::uint64_t weight)
{
	std::uint64_t j, k, totalweight;
	float bound;
	
	j = k = totalweight = 0;
	bound = 0.0;
	if(weight >= W)
		return false;
	j = i + 1;
	bound = profit;
	totalweight = weight;
	while(j < n && totalweight + w[j] <= W)
	{
		totalweight += w[j];
		bound += p[j];
		j++;
	}
	k = j;
	if(k < n)
	{
		bound += (W - totalweight) * (float) (p[k] / w[k]);
	}
	return bound > maxprofit;
}

void
knapsack(std::uint64_t i, std::uint64_t profit, std::uint64_t weight)
{
	if(weight <= W && profit > maxprofit)
	{
		maxprofit = profit;
		numbest = i;
		bestset = include;
	}
	if(promising(i, profit, weight))
	{
		include[i + 1] = 'y';
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = 'n';
		knapsack(i + 1, profit, weight);
	}
	return;
}

void
usage(void)
{
	std::cout << "usage: backtracking [filename]" << std::endl;
	return;
}

void
initpq(pqueue& pq, std::ifstream& fd)
{
	std::uint64_t n, W;
	itemptr* items;

	fd >> n;
	fd >> W;
	std::cout << "got n " << n << " got W " << W << std::endl;
	items = new itemptr[n];
	w = new std::uint64_t[n];
	p = new std::uint64_t[n];
	include = new char[n];
	for(std::uint64_t i = 0; i < n; i++)
	{
		items[i] = new item();
		fd >> items[i]->name;
		fd >> items[i]->profit;
		fd >> items[i]->weight;
		items[i]->ratio = (double) items[i]->profit /
						  (double) items[i]->weight;
		pq.enqueue(items[i]);
	}
}

void
initarr(pqueue& pq)
{
	itemptr item;
	uint64_t i;

	i = 0;
	std::cout << "in initarr" << std::endl;
	while((item = pq.dequeue()) != nullptr)
	{
		names.push_back(item->name);
		p[i] = item->profit;
		w[i] = item->weight;
		i++;
	}
}

int
main(int argc, char* argv[])
{
	pqueue pq;
	std::uint64_t index;

	n = W = numbest = maxprofit = index = solweight = 0;
	w = p = nullptr;
	include = nullptr;
	if(argc != 2)
	{
		usage();
		exit(1);
	}
	std::ifstream filestream(argv[1]);
	initpq(pq, filestream);
	std::cout << "initialized priority queue" << std::endl;
	initarr(pq);
	std::cout << "initialized array" << std::endl;
	std::cout << "array:" << std::endl;
	for(std::uint64_t i = 0; i < n; i++)
	{
		std::cout << names[i] << " ";
		std::cout << p[i] << " ";
		std::cout << w[i] << " ";
		std::cout << std::endl;
	}
	knapsack(index, maxprofit, solweight);
	std::cout << "found knapsack solution" << std::endl;
	std::cout << "max profit: " << maxprofit << std::endl;
	std::cout << "solution weight: " << solweight << std::endl;
	std::cout << "items chosen: ";
	for(uint64_t i = 0; i < n; i++)
		std::cout << i << ": " << include[i] << " ";
	std::cout << std::endl;
	exit(0);
}