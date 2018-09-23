#include <stdint.h>
#include <stdlib.h>

struct
item
{
	char name[64];
	uint64_t weight;
	uint64_t profit;
	float ratio;
};

struct
node
{
	item* i;
	node* next;
};

struct
pqueue
{
	node* front;
	int (*enqueue) (pqueue*, item);
	item* (*dequeue) (pqueue*);
};

int enqueue(pqueue*, item*);
item* dequeue(pqueue*);
