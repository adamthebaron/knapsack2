#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "priorityqueue.hpp"

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
int genfile(uint64_t, uint64_t);
void writesolfile(struct knapsack*);
uint64_t genrand(uint64_t);
uint64_t initpq(struct pqueue*, std::ifstream*);
void steal(struct pqueue*, struct knapsack*);
