#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <fstream>

#include "priorityqueue.hpp"

struct item nullitem = {
	/* name */ "null item",
	/* weight */ 0,
	/* profit */ 0,
	/* ratio */ 0
};


struct knapsack {
	uint64_t capacity;
	uint64_t sol_item_num;
	uint64_t sol_weight;
	uint64_t sol_profit;
	struct item sol_items[1024];
};

void usage(void);
int genfile(uint64_t, uint64_t);
void writesolfile(struct knapsack*);
uint64_t genrand(uint64_t);
uint64_t initpq(struct pqueue*, std::ifstream*, struct item**);
void steal(struct pqueue*, struct knapsack*);
