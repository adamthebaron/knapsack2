#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <inttypes.h>

struct
item
{
	std::string name;
	uint64_t weight;
	uint64_t profit;
	double ratio;
};

struct
node
{
	item* i;
	node *parent, *left, *right;
};

typedef node* nodeptr;

class
pqueue
{
	private:
		struct node* root;
		uint64_t size;
		void _enqueue(item* i, nodeptr& n, nodeptr& p);
		node* _dequeue(nodeptr n);
		void _delete(nodeptr& n);

	public:
		void enqueue(item* i);
		item dequeue(void);
		void Delete(node* n);
		void setSize(uint64_t size);
		uint64_t getSize(void);
};
