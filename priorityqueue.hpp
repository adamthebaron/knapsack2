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
	void print() {
		std::cout << "name: " << name << " weight: " << weight << " profit: " << profit << " ratio: " << ratio << std::endl;
	}
};

struct
node
{
	item* i;
	node *parent, *left, *right;
	node()
	{
		i = NULL;
		parent = left = right = NULL;
	}
	node(item* curitem)
	{
		i = curitem;
		parent = left = right = NULL;
	}
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
		void _traversal(nodeptr n);

	public:
		void enqueue(item* i);
		item* dequeue();
		uint64_t getSize() const;
		void traversal();
		pqueue()
		{
			root = NULL;
			size = 0;
		}
};
