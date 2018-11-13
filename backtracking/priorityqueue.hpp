#ifndef _PRIORITYQUEUE_HPP_
#define _PRIORITYQUEUE_HPP_

#include <cstdint>
#include <iostream>
#include <string>

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
		i = nullptr;
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
		struct node* root;
		uint64_t size;
		void _enqueue(item* i, nodeptr& n, nodeptr& p);
		node* _dequeue(nodeptr n);
		void _traversal(nodeptr n);
		itemptr& _top(nodeptr n);

	public:
		void enqueue(item* i);
		item* dequeue();
		uint64_t getSize() const;
		itemptr& top(void);
		void traversal();
		pqueue()
		{
			root = nullptr;
			size = 0;
		}
};

#endif