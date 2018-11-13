#include "backtrack.hpp"

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
	bt.include = new std::string*[n];
	bt.setn(n);
	bt.setW(W);
	for(std::uint64_t i = 0; i < n; i++)
	{
		items[i] = new item();
		bt.include[i] = new std::string();
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
		std::cout << "adding item " << item->name 
				  << " to index " << i << std::endl;
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
	bt.knapsack(0);
	std::cout << "found knapsack solution" << std::endl;
	std::cout << "max profit: " << bt.maxprofit << std::endl;
	std::cout << "items chosen: ";
	for(uint64_t i = 0; i < bt.numbest; i++)
		std::cout << *(bt.bestset[i]) << " ";
	std::cout << std::endl;
	exit(0);
}