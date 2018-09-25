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

extern struct item nullitem;

struct
node
{
	struct item* i;
	struct node *parent, *left, *right;
};

struct
pqueue
{
	struct node* root;
	uint64_t size;
	//void (*enqueue) (pqueue*, item*);
	//item* (*dequeue) (pqueue*);
};

void enqueue(struct pqueue*, struct item*);
struct node* _enqueue(struct pqueue*, struct item* i, struct node* n);
struct item _dequeue(struct pqueue* pq, struct node* n);
struct item dequeue(struct pqueue*);
