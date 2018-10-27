#include "main.hpp"

void
usage(void)
{
	printf("knapsack [filename]\n");
	return;
}

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

void
printarr(uint64_t& arr[][], uint64_t m, uint64_t n)
{
	for(uint64_t i = 0; i < m; i++)
	{
		for(uint64_t j = 0; j < n; j++)
		{
			std::cout << arr[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

uint64_t 
memoize(uint64_t weight, uint64_t n, uint64_t *weights, uint64_t *values) 
{ 
   uint64_t memo[n + 1][weight + 1]; 

   for (uint64_t i = 0; i <= n; i++) 
   { 
       for (uint64_t w = 0; w <= weight; w++) 
       { 
           if (i==0 || w==0) 
               memo[i][w] = 0; 
           else if (wt[i-1] <= w) 
                 memo[i][w] = max(values[i-1] + memo[i-1][w-weights[i-1]], memo[i-1][w]); 
           else
                 memo[i][w] = memo[i-1][w]; 
       }
   }
   printarr(memo, n, w);
   return memo[n][w]; 
} 

int
main(int argc, const char* argv[])
{
	std::string filename;
	std::ifstream fd;
	struct knapsack* joulethief;
	uint64_t maxval;
	uint64_t weight;
	uint64_t itemnum;
	uint64_t *weights;
	uint64_t *values;

	if(argc == 1 || argc > 2)
	{
		usage();
		exit(0);
	}
	maxval = weight = itemnum = 0;
	filename = argv[1];
	joulethief = new knapsack();
	fd.open(filename, std::ios::in);
	maxval = memoize(weight, itemnum, weights, values);
	std::cout << "maximum value for knapsack of size " << weight << " is " << maxval << std::endl;
	fd.close();
	delete joulethief;
	delete weights;
	delete values;
	exit(0);
}
