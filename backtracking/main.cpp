#include <fstream>
#include <vector>

#include "priorityqueue.hpp"

std::uint64_t* w;
std::uint64_t* p;
std::vector<std::string> names;
char* include;

bool
promising(std::uint64_t i, std::uint64_t profit, std::uint64_t weight)
{
	return true;
}

void
knapsack(std::uint64_t& i, std::uint64_t& profit, std::uint64_t& weight)
{
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
	std::uint64_t n, W, numbest, solweight, maxprofit, index;

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