#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <inttypes.h>

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
uint64_t genrand(void);
int initpq(pqueue*, FILE*);
int steal(pqueue*, knapsack*);
