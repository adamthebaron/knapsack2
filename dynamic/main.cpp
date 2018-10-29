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

uint64_t
maximum(uint64_t a, uint64_t b)
{
	return a ? a > b : b;
}

typedef struct item item;

class knapsack {
	public:
	int64_t capacity;
	uint64_t sol_item_num;
	uint64_t sol_weight;
	uint64_t sol_profit;
	item* sol_items;
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
		delete sol_items;
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
memoize(uint64_t**& memo, uint64_t weight, uint64_t n, item* items) 
{ 
	std::cout << "weight of knapsack is " << weight << " number of items is " << n << std::endl;
	for (uint64_t i = 0; i <= n; i++) 
   { 
       for (uint64_t w = 0; w <= weight; w++) 
       { 
           if (i==0 || w==0)
		   {
			   std::cout << "i is " << i << " w is " << w << " setting memo of i of w to 0" << std::endl;
               memo[i][w] = 0; 
		   }
           else if (items[i-1].weight <= w)
		   {
				std::cout << "weight of item " << items[i-1].name << " (" << items[i-1].weight << ") less than or equal to " << w;
				std::cout << std::endl << " finding max of " << items[i-1].profit + memo[i-1][w-items[i-1].weight] << " " << memo[i-1][w] << std::endl;
            	memo[i][w] = maximum(items[i-1].profit + memo[i-1][w-items[i-1].weight], memo[i-1][w]);
				std::cout << "max is " << memo[i][w] << std::endl;
		   }
           else if (items[i-1].weight > w)
		   {
			   	std::cout << "not doing anything setting memo of i of w to memo of i - 1 of w (" << memo[i - 1][w] << ")" << std::endl;
                 memo[i][w] = memo[i-1][w];
		   }
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
	uint64_t maxval;
	uint64_t weight;
	uint64_t itemnum;
	uint64_t** memo;
	item* items;

	// if(argc != 2)
	// {
	// 	usage();
	// 	exit(0);
	// }
	maxval = weight = itemnum = 0;
	//filename = argv[1];
	fd.open("examplefile", std::ios::in);
	fd >> itemnum >> weight;
	std::cout << "got itemnum " << itemnum << " and knapsack weight " << weight << std::endl;
	items = new item[itemnum];
	memo = new uint64_t*[itemnum];
	for(uint64_t i = 0; i < itemnum; i++)
	{
		memo[i] = new uint64_t[weight];
	}
	for(uint64_t i; i < itemnum; i++)
	{
		fd >> items[i].name >> items[i].profit >> items[i].weight;
		std::cout << "added item ";
		std::cout << items[i].name << " ";
		std::cout << items[i].profit << " ";
		std::cout << items[i].weight << std::endl;
	}
	joulethief = new knapsack();
	joulethief->capacity = weight;
	maxval = memoize(memo, weight, itemnum, items);
	std::cout << "maximum value for knapsack of size " << weight << " is " << maxval << std::endl;
	fd.close();
	delete joulethief;
	delete items;
	for(uint64_t i = 0; i < itemnum; i++)
	{
		delete memo[i];
	}
	delete memo;
	exit(0);
}
