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
	int64_t weight;
	uint64_t profit;
	double ratio;
	void print()
	{
		std::cout << "name: " << name << " weight: " << weight << " profit: " << profit << " ratio: " << ratio << std::endl;
	}
	item()
	{
		weight = 0;
		profit = 0;
		ratio = 0.0;
		name = "";
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
		parent = left = right = nullptr;
	}
	node(item* curitem)
	{
		i = curitem;
		parent = left = right = nullptr;
	}
};

typedef node* nodeptr;
typedef item* itemptr;

class
pqueue
{
	private:
		nodeptr root;
		uint64_t size;
		void _enqueue(itemptr i, nodeptr& n, nodeptr& p);
		nodeptr _dequeue(nodeptr n);
		void _traversal(nodeptr n);

	public:
		void enqueue(itemptr i);
		itemptr dequeue();
		uint64_t getSize() const;
		void traversal();
		pqueue()
		{
			root = NULL;
			size = 0;
		}
};
