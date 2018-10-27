#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

struct knapsack {
	int64_t capacity;
	uint64_t sol_item_num;
	uint64_t sol_weight;
	uint64_t sol_profit;
	struct item* sol_items[10000];
	knapsack()
	{
		sol_item_num = sol_weight = sol_profit = 0;
		capacity = 0;
	}
	void string()
	{
		std::cout << "capacity: " << capacity << " sol_item_num: " << sol_item_num << " sol_weight: " << sol_weight << " sol_profit: " << sol_profit << std::endl;
	}
};

void usage(void);
void writesolfile(struct knapsack*);
void printarr(uint64_t**, uint64_t, uint64_t);
uint64_t memoize(uint64_t, uint64_t, uint64_t*, uint64_t*);
