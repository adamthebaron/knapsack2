#include <fstream>
#include <vector>

#include "priorityqueue.hpp"

std::vector<uint64_t> w;
std::vector<uint64_t> p;
uint64_t n, W, numbest, solweight, maxprofit;
std::vector<std::string> names;
std::vector<char> include;
std::vector<char> bestset;
pqueue pq;

bool
promising(uint64_t i, uint64_t profit, uint64_t weight)
{
	uint64_t j, k, totalweight;
	float bound;
	
	j = k = totalweight = 0;
	bound = 0.0;
	if(weight >= W)
		return false;
	j = i + 1;
	bound = profit;
	totalweight = weight;
	while(j <= n && (totalweight + w[j]) <= W)
	{
		totalweight += w[j];
		bound += p[j];
		j++;
	}
	k = j;
	if(k <= n)
	{
		bound += (W - totalweight) * (float) (p[k] / w[k]);
	}
	//std::cout << "bound is " << bound << " maxprofit: " << maxprofit << std::endl;
	return bound > maxprofit;
}

void
knapsack(uint64_t i, uint64_t profit, uint64_t weight)
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
initpq(std::ifstream& fd)
{
	itemptr* items;

	fd >> n;
	fd >> W;
	//std::cout << "got n " << n << " got W " << W << std::endl;
	items = new itemptr[n];
	for(uint64_t i = 0; i < n; i++)
	{
		items[i] = new item();
		fd >> items[i]->name;
		fd >> items[i]->profit;
		fd >> items[i]->weight;
		items[i]->ratio = (double) items[i]->profit /
						  (double) items[i]->weight;
        //std::cout << "enqueuing " << items[i]->name << std::endl;
		pq.enqueue(items[i]);
	}
}

void
initarr()
{
	itemptr item;
	uint64_t i;

	i = 0;
	//std::cout << "in initarr" << std::endl;
	p.push_back(0);
	w.push_back(0);
	include.push_back('n');
	while((item = pq.dequeue()) != NULL)
	{
        names.push_back(item->name);
		p.push_back(item->profit);
		w.push_back(item->weight);
        include.push_back('n');
		//std::cout << "dequeueing " << names[i] << " " << p[i] << " " << w[i] << std::endl;
        i++;
	}
}

int
main(int argc, char* argv[])
{
	uint64_t index;
    uint64_t profit, weight;
	std::vector<std::string> chosenItems;

	profit = weight = n = W = numbest = maxprofit = index = solweight = 0;
	if(argc != 2)
	{
		usage();
		exit(1);
	}
	std::ifstream filestream(argv[1]);
	initpq(filestream);
	//std::cout << "initialized priority queue n " << n << " w: " << W << std::endl;
	initarr();
	//std::cout << "initialized array" << std::endl;
	//std::cout << "array:" << std::endl;
	/*for(uint64_t i = 0; i < n; i++)
	{
        std::cout << i << ": ";
        std::cout << names[i] << " ";
		std::cout << p[i] << " ";
		std::cout << w[i] << " ";
		std::cout << std::endl;
	}*/
	knapsack(index, profit, weight);
	for(uint64_t i = 0; i < include.size(); i++)
	{
		if(bestset[i] == 'y')
		{
			solweight += w[i];
			chosenItems.push_back(names[i - 1]);
		}
	}
	std::cout << "found knapsack solution" << std::endl;
	std::cout << "max profit: " << maxprofit << std::endl;
	std::cout << "solution weight: " << solweight << std::endl;
	std::cout << "items chosen: ";
	for(std::string chosenItem : chosenItems)
		std::cout << chosenItem << std::endl;
	exit(0);
}
