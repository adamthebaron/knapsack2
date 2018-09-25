#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

struct
item
{
	char name[64];
	uint64_t weight;
	uint64_t profit;
	double ratio;
};

extern item nullitem;

struct
node
{
	item* i;
	node *parent, *left, *right;
};

struct
pqueue
{
	node* root;
	uint64_t size;
	//void (*enqueue) (pqueue*, item*);
	//item* (*dequeue) (pqueue*);
};

void enqueue(pqueue* pq, item* i);
node* _enqueue(pqueue* pq, item* i, node* n);
item _dequeue(pqueue* pq, node* n);
item dequeue(pqueue*);
