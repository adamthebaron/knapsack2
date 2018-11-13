#include "priorityqueue.hpp"

uint64_t
pqueue::getSize(void) const
{
	return size;
}

void
pqueue::_enqueue(itemptr i, nodeptr& n, nodeptr& p)
{
	nodeptr parent = p;
	if (root == nullptr)
	{
		parent = nullptr;
	}
	if(n == nullptr)
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

nodeptr
pqueue::_dequeue(nodeptr n)
{
	if(n->right != nullptr)
	{
		return _dequeue(n->right);
	}
	else if(n->left != nullptr)
	{
		n->left->parent = n->parent;
		if(n->parent != nullptr)
			n->parent->right = n->left;
		else
			root = n->left;
	}
	else
	{
		if(n->parent != nullptr)
			n->parent->right = nullptr;
		else
			root = nullptr;
	}
	return n;
}

itemptr
pqueue::dequeue(void)
{
	nodeptr n; 
	nodeptr p;

	if(root == nullptr)
		return nullptr;
	n = this->_dequeue(this->root);
	return n->i;
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
