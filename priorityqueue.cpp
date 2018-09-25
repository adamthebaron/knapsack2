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

node*
pqueue::_enqueue(item* i, node* n)
{
	if(n == NULL)
	{
		printf("found null leaf, going here\n");
		n = new node();
		memset(n, 0, sizeof(struct node));
		n->i = i;
		n->left = n->right = NULL;
		return n;
	}
	else
	{
		if(n->i->ratio < i->ratio)
		{
			printf("%f is less than %f, going left\n", n->i->ratio, i->ratio);
			n->left = this->_enqueue(i, n->left);
		}
		else if(n->i->ratio > i->ratio)
		{
			printf("%f is greater than %f, going right\n", n->i->ratio, i->ratio);
			n->right = this->_enqueue(i, n->right);
		}
		else if(n->i->ratio == i->ratio)
		{
			printf("%f is equal to %f, checking profit\n", n->i->ratio, i->ratio);
			printf("profits are %" PRIu64 " and %" PRIu64 "\n", n->i->profit, i->profit);
			if(n->i->profit < i->profit)
			{
				printf("%" PRIu64 "is less than %" PRIu64 ", going left\n", n->i->profit, i->profit);
				n->left = this->_enqueue(i, n->left);
			}
			else if(n->i->profit > i->profit)
			{
				printf("%" PRIu64 "is greater than %" PRIu64 ", going right\n", n->i->profit, i->profit);
				n->right = this->_enqueue(i, n->right);
			}
			else if(n->i->profit == i->profit)
			{
				printf("profits are the same just go to the left fuck it\n");
				n->left = this->_enqueue(i, n->left);
			}
		}
		return n;
	}
}

void
pqueue::enqueue(item* i)
{
	this->root = this->_enqueue(i, this->root);
	return;
}

item
pqueue::_dequeue(node* n)
{
	if(n == NULL)
		return nullitem;
	if(n->right != NULL)
		return this->_dequeue(n->right);
	if(n->left != NULL)
		return this->_dequeue(n->left);
	item i;
	printf("copying item %s\n", n->i->name);
	memcpy(&i, n->i, sizeof(struct item));
	printf("copied %s\n", i.name);
	printf("freeing node %s\n", i.name);
	delete n;
	return i;
}

item
pqueue::dequeue(void)
{
	return this->_dequeue(this->root);
}
