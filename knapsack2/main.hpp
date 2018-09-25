#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#include "priorityqueue.hpp"

struct knapsack {
	uint64_t capacity;
	uint64_t sol_item_num;
	uint64_t sol_weight;
	uint64_t sol_profit;
	item* sol_items[];
};

void usage(void);
int genfile(uint64_t, uint64_t);
void writesolfile(knapsack*);
uint64_t genrand(void);
uint64_t initpq(pqueue*, FILE*);
void steal(pqueue*, knapsack*);
