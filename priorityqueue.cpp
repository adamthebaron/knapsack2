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
		n->i = i;
		n->left = n->right = NULL;
		return n;
	}
	else
	{
		if(i->ratio < n->i->ratio)
		{
			printf("%f is less than %f, going left\n", i->ratio, n->i->ratio);
			n->left = this->_enqueue(i, n->left);
		}
		else if(i->ratio > n->i->ratio)
		{
			printf("%f is greater than %f, going right\n", i->ratio, n->i->ratio);
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

node*
pqueue::_dequeue(node* n)
{
	if(n->right != NULL)
	{
		n->right = this->_dequeue(n->right);
		return n;
	}
	else
	{
		this->size--;
		/* node we need has no children */
		if(n->left == NULL)
			return n;
		/* node we need has a left child */
		node* tmp;
		tmp = n;
		n = n->left;
		while(n->right != NULL)
		{
			n = n->right;

		}
	}
}

node*
pqueue::_delete(node* n, node* root)
{
	if(root == NULL)
		return NULL;
	if(n->i->ratio < root->i->ratio)
	{
		root->left = this->_delete(n, root->left);
		return root;
	}
	else if(n->i->ratio > root->i->ratio)
	{
		root->right = this->_delete(n, root->right);
		return root;
	}
	else
	{
		this->size--;
		if(root->left == NULL && root->right == NULL)
			return NULL;
		if(root->right == NULL)
			return root->left;
		if(root->left == NULL);
			return root->right;
	}
}

void
pqueue::Delete(node* n)
{
	this->_delete(n, this->root);
	return;
}

item
pqueue::dequeue(void)
{
	item i;
	node *max, *pos;

	pos = this->root;
	while(pos->right != NULL)
	{
		pos = pos->right;
	}
	max = pos;
	strcpy(i.name, max->i->name);
	i.profit = max->i->profit;
	i.weight = max->i->weight;
	i.ratio = max->i->ratio;
	this->Delete(max);
	return i;
}
