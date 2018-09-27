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
		//std::cout << "enqueuing item " << n->i->name << std::endl;
		n->parent = parent;
		//std::cout << "setting parent to " << n->parent << std::endl;
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
	//std::cout << "at node " << n->i->name << std::endl;
	if(n->right != NULL)
	{
		//std::cout << "right child not null going to " << n->right->i->name << std::endl;
		return _dequeue(n->right);
	}
	else if(n->left != NULL)
	{
		//std::cout << "left child " << n->left->i->name << " not null need to set some pointers" << std::endl;
		n->left->parent = n->parent;
		if(n->parent != NULL)
			n->parent->right = n->left;
		else
			root = n->left;
		//std::cout << "gucci" << std::endl;
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
	//std::cout << "got item " << n->i->name << std::endl;
	return n->i;
}

void
pqueue::_traversal(nodeptr n)
{
	if(n == NULL)
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
