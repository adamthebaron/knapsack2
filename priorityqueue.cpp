#include "priorityqueue.hpp"

uint64_t
pqueue::getSize(void)
{
	return this->size;
}

void
pqueue::setSize(uint64_t size)
{
	this->size = size;
}

void
pqueue::_enqueue(item* i, nodeptr& n, nodeptr& p)
{
	if(n == NULL)
	{
		printf("found null leaf, going here\n");
		n = new node();
		n->i = i;
		n->left = n->right = NULL;
		if(p == NULL)
			n->parent = NULL;
		else
			n->parent = p;
		return;
	}
	else
	{
		if(i->ratio < n->i->ratio)
		{
			std::cout << i->ratio << " is less than ratio " << n->i->ratio << " on item " << n->i->name << " going left" << std::endl;
			this->_enqueue(i, n->left, n);
		}
		if(i->ratio > n->i->ratio)
		{
			std::cout << i->ratio << " is greater than ratio " << n->i->ratio << " on item " << n->i->name << " going right" << std::endl;
			this->_enqueue(i, n->right, n);
		}
		if(n->i->ratio == i->ratio)
		{
			printf("%f is equal to %f, checking profit\n", n->i->ratio, i->ratio);
			printf("profits are %" PRIu64 " and %" PRIu64 "\n", n->i->profit, i->profit);
			if(n->i->profit < i->profit)
			{
				printf("%" PRIu64 "is less than %" PRIu64 ", going left\n", n->i->profit, i->profit);
				this->_enqueue(i, n->left, n);
			}
			else if(n->i->profit > i->profit)
			{
				printf("%" PRIu64 "is greater than %" PRIu64 ", going right\n", n->i->profit, i->profit);
				this->_enqueue(i, n->right, n);
			}
			else if(n->i->profit == i->profit)
			{
				printf("profits are the same just go to the left\n");
				this->_enqueue(i, n->left, n);
			}
		}
		return;
	}
}

void
pqueue::enqueue(item* i)
{
	this->_enqueue(i, this->root, this->root);
	return;
}

void
pqueue::_delete(nodeptr &n)
{
	std::cout << "at node " << n->i->name << std::endl;
	if(n->right != NULL)
		this->_delete(n->right);
	if(n->right == NULL && n->left != NULL)
	{
		std::cout << "setting " << n->i->name << " to be replaced by " << n->left->i->name << std::endl;
		n = n->left;
		std::cout << "n now has a left child of " << n->left->i->name << std::endl;
		return;
	}
	return;
}

node*
pqueue::_dequeue(nodeptr n)
{
	std::cout << "looking at node " << n->i->name;
	std::cout << " with parent stuff " << n->parent->i->name << std::endl;
	if(n == NULL)
		return NULL;
	if(n->right != NULL)
	{
		std::cout << "going to " << n->right->i->name <<  " from " << n->i->name << std::endl;
		n->right = this->_dequeue(n->right);
	}
	if(n->left == NULL)
		return n;
	std::cout << "returning " << n->i->name << std::endl; //" to " << n->left->i->name << std::endl;
	std::cout << "setting " << n->parent->i->name << " to have a left child of " << n->left->i->name << std::endl;
	n->parent->right = n->left;
	return n;
}

item
pqueue::dequeue(void)
{
	node* n, *p;
	item i;

	n = this->_dequeue(this->root);
	i.name = n->i->name;
	i.profit = n->i->profit;
	i.weight = n->i->weight;
	i.ratio = n->i->ratio;
	return i;
}

/*
item
pqueue::dequeue(void)
{
	/* to dequeue, find max node,
	 * copy it from the heap
	 * then change parent pointer stuff 
	nodeptr n;
	item i;

	n = this->root;
	n->parent = this->root;
	std::cout << "starting at node " << this->root->i->name << std::endl;
	while(n->right != NULL)
	{
		std::cout << "going to node " << n->right->i->name << std::endl;
		n->parent = n;
		n = n->right;
	}
	std::cout << "finished at node " << n->i->name << std::endl;
	i.name = n->i->name;
	i.profit = n->i->profit;
	i.weight = n->i->weight;
	i.ratio = n->i->ratio;
	std::cout << "setting new parent stuff" << std::endl;
	n->parent->right = n->left;
	return i;
}
*/