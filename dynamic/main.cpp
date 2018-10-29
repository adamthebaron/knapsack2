#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdint>

struct item
{
	std::string name;
	uint64_t profit;
	uint64_t weight;
};

typedef struct item item;

class knapsack {
	public:
	int64_t capacity;
	uint64_t sol_item_num;
	uint64_t sol_weight;
	uint64_t sol_profit;
	struct item* sol_items[10000];
	knapsack()
	{
		this->sol_item_num = this->sol_weight = this->sol_profit = 0;
		capacity = 0;
	}
	void string()
	{
		std::cout << "capacity: " << this->capacity;
		std::cout << " sol_item_num: " << this->sol_item_num;
		std::cout << " sol_weight: " << this->sol_weight;
		std::cout << " sol_profit: " << this->sol_profit << std::endl;
	}
	~knapsack()
	{
		delete [] sol_items;
	}
};
typedef struct item item;

void
usage(void)
{
	printf("knapsack [filename]\n");
	return;
}

/*
void
writesolfile(struct knapsack* ksack)
{
	std::cout << ksack->sol_item_num << std::endl;
	std::cout << ksack->sol_weight << std::endl;
	std::cout << ksack->sol_profit << std::endl;
	for(uint64_t i = 0; i < ksack->sol_item_num; i++)
	{
		std::cout << ksack->sol_items[i]->name << " " << ksack->sol_items[i]->profit << " " << ksack->sol_items[i]->weight << std::endl;
	}
	return;
}
*/

void
printarr(uint64_t** arr, uint64_t m, uint64_t n)
{
	for(uint64_t i = 0; i < m; i++)
	{
		for(uint64_t j = 0; j < n; j++)
		{
			std::cout << arr[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	return;
}

uint64_t 
memoize(uint64_t** memo, uint64_t weight, uint64_t n, item* items) 
{ 
	for (uint64_t i = 0; i <= n; i++) 
   { 
       for (uint64_t w = 0; w <= weight; w++) 
       { 
           if (i==0 || w==0) 
               memo[i][w] = 0; 
           else if (items[i-1].weight <= w) 
                 memo[i][w] = std::max(items[i-1].profit + memo[i-1][w-items[i-1].weight], memo[i-1][w]); 
           else
                 memo[i][w] = memo[i-1][w]; 
       }
   }
   printarr(memo, n, weight);
   return memo[n][weight]; 
} 

int
main(int argc, const char* argv[])
{
	std::string filename;
	std::ifstream fd;
	knapsack* joulethief;
	uint64_t** memo;
	uint64_t maxval;
	uint64_t weight;
	uint64_t itemnum;
	item* items;

	if(argc != 2)
	{
		usage();
		exit(0);
	}
	maxval = weight = itemnum = 0;
	filename = argv[1];
	std::istringstream input(filename);
	input >> itemnum >> weight;
	items = new item[itemnum];
	for(uint64_t i; i < itemnum; i++)
	{
		input >> items[i].name >> items[i].profit >> items[i].weight;
	}
	joulethief = new knapsack();
	joulethief->capacity = weight;
	fd.open(filename, std::ios::in);
	maxval = memoize(memo, weight, itemnum, items);
	std::cout << "maximum value for knapsack of size " << weight << " is " << maxval << std::endl;
	fd.close();
	delete joulethief;
	delete items;
	exit(0);
}
