#include "priorityqueue.hpp"

uint64_t
pqueue::getSize(void) const
{
	return size;
}

void
pqueue::_enqueue(item* i, nodeptr& n, nodeptr& p)
{
	node* parent = p;
	if (root == NULL)
	{
		parent = NULL;
	}
	if(n == NULL)
	{
		n = new node();
		n->i = i;
		n->parent = parent;
		return;
	}
	else
	{
		if(i->ratio < n->i->ratio)
		{
			_enqueue(i, n->left, n);
		}
		if(i->ratio > n->i->ratio)
		{
			_enqueue(i, n->right, n);
		}
		if(n->i->ratio == i->ratio)
		{
			if(n->i->profit < i->profit)
			{
				_enqueue(i, n->left, n);
			}
			else if(n->i->profit > i->profit)
			{
				_enqueue(i, n->right, n);
			}
			else if(n->i->profit == i->profit)
			{
				_enqueue(i, n->left, n);
			}
		}
		return;
	}
}

void
pqueue::enqueue(item* i)
{
	_enqueue(i, root, root);
	return;
}

node*
pqueue::_dequeue(nodeptr n)
{
	if(n->right != NULL)
	{
		return _dequeue(n->right);
	}
	else if(n->left != NULL)
	{
		n->left->parent = n->parent;
		if(n->parent != NULL)
			n->parent->right = n->left;
		else
			root = n->left;
	}
	else
	{
		if(n->parent != NULL)
			n->parent->right = NULL;
		else
			root = NULL;
	}
	return n;
}

item*
pqueue::dequeue(void)
{
	nodeptr n; 
	nodeptr p;

	if(root == NULL)
		return NULL;
	n = this->_dequeue(this->root);
	return n->i;
}

itemptr&
pqueue::_top(nodeptr n)
{
	if(n->right != nullptr)
		_top(n->right);
	return n->i;
}

itemptr&
pqueue::top()
{
	return _top(root);
}

void
pqueue::_traversal(nodeptr n)
{
	if(n == nullptr)
		return;
	n->i->print();
	_traversal(n->left);
	_traversal(n->right);
}

void
pqueue::traversal()
{
	_traversal(root);
}
