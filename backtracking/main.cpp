#include "priorityqueue.hpp"

#include <fstream>

void
usage(void)
{
	std::cout << "usage: backtracking [filename]" << std::endl;
	return;
}

void
initpq(Backtrack& bt, std::ifstream& fd)
{
	item** items;
	std::uint64_t n, W;

	fd >> n;
	fd >> W;
	items = new item*[n];
	bt.items = new item[n];
	bt.include = new bool[n];
	bt.setn(n);
	bt.setW(W);
	for(std::uint64_t i = 0; i < n; i++)
	{
		items[i] = new item();
		fd >> items[i]->name;
		fd >> items[i]->profit;
		fd >> items[i]->weight;
		items[i]->ratio = (double) items[i]->profit /
						  (double) items[i]->weight;
		bt.enqueue(items[i]);
	}
}

void
initarr(Backtrack& bt)
{
	itemptr item;
	uint64_t i;
	
	i = 0;
	std::cout << "in initarr" << std::endl;
	while((item = bt.pq.dequeue()) != NULL)
	{
		bt.items[i].name = item->name;
		bt.items[i].profit = item->profit;
		bt.items[i].weight = item->weight;
		bt.items[i].ratio = item->ratio;
		i++;
	}
	
}

int
main(int argc, char* argv[])
{
	std::uint64_t maxprofit, solweight, numbest, index;
	
	maxprofit = solweight = numbest = index = 0;
	if(argc != 2)
	{
		usage();
		exit(1);
	}
	std::ifstream filestream(argv[1]);
	Backtrack bt;
	initpq(bt, filestream);
	std::cout << "initialized priority queue" << std::endl;
	initarr(bt);
	std::cout << "initialized array" << std::endl;
	std::cout << "array:" << std::endl;
	for(std::uint64_t i = 0; i < bt.n; i++)
	{
		std::cout << bt.items[i].name << " ";
		std::cout << bt.items[i].profit << " ";
		std::cout << bt.items[i].weight << " ";
		std::cout << bt.items[i].ratio;
		std::cout << std::endl;
	}
	bt.knapsack(index, maxprofit, solweight);
	std::cout << "found knapsack solution" << std::endl;
	std::cout << "max profit: " << maxprofit << std::endl;
	std::cout << "solution weight: " << solweight << std::endl;
	std::cout << "items chosen: ";
	for(uint64_t i = 0; i < bt.n; i++)
		std::cout << i << ": " << bt.include[i] << " ";
	std::cout << std::endl;
	exit(0);
}