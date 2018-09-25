#include "priorityqueue.hpp"

node*
_enqueue(pqueue* pq, item* i, node* n)
{
	if(n == NULL)
	{
		n = (node*) calloc(1, sizeof(node));
		n->i = i;
		n->left = n->right = NULL;
		return n;
	}
	else
	{
		if(n->i->ratio < i->ratio)
			n->left = _enqueue(pq, i, n->left);
		else if(n->i->ratio > i->ratio)
			n->right = _enqueue(pq, i, n->right);
		return n;
	}
}

void enqueue(pqueue* pq, item* i)
{
	pq->root = _enqueue(pq, i, pq->root);
	(pq->size)++;
	return;
}

item*
dequeue(pqueue* pq)
{
	item* ret;
	if(pq->root == NULL)
		return NULL;
	ret = pq->root->i;
	(pq->size)--;
	return ret;
}
