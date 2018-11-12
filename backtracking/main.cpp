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
	exit(0);
}