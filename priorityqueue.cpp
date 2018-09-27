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
		n = new node();
		n->i = i;
		n->left = n->right = NULL;
		if(p == NULL)
			n->parent = NULL;
		else
		{
			n->parent = p;
		}
		return;
	}
	else
	{
		if(i->ratio < n->i->ratio)
		{
			this->_enqueue(i, n->left, n);
		}
		if(i->ratio > n->i->ratio)
		{
			this->_enqueue(i, n->right, n);
		}
		if(n->i->ratio == i->ratio)
		{
			if(n->i->profit < i->profit)
			{
				this->_enqueue(i, n->left, n);
			}
			else if(n->i->profit > i->profit)
			{
				this->_enqueue(i, n->right, n);
			}
			else if(n->i->profit == i->profit)
			{
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

node*
pqueue::_dequeue(nodeptr n)
{
	/*std::cout << "looking at node " << n->i->name;
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
	return n;*/

	if(n->right != NULL)
		n->right = this->_dequeue(n->right);
	if(n->left != NULL)
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