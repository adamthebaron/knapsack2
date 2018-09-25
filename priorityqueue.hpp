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

class
pqueue
{
	private:
		struct node* root;
		uint64_t size;
		node* _enqueue(item* i, node* n);
		item _dequeue(node* n);
	
	public:
		void enqueue(item* i);
		item dequeue(void);
		void setSize(uint64_t);
		uint64_t getSize(void);
};
