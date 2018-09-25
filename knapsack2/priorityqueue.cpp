#include "priorityqueue.hpp"

node*
_enqueue(pqueue* pq, item* i, node* n)
{
	if(n == NULL)
	{
		printf("found null leaf, going here\n");
		n = (node*) calloc(1, sizeof(node));
		memset(n, 0, sizeof(node));
		n->i = i;
		n->left = n->right = NULL;
		return n;
	}
	else
	{
		if(n->i->ratio < i->ratio)
		{
			printf("%f is less than %f, going left\n", n->i->ratio, i->ratio);
			n->left = _enqueue(pq, i, n->left);
		}
		else if(n->i->ratio > i->ratio)
		{
			printf("%f is greater than %f, going right\n", n->i->ratio, i->ratio);
			n->right = _enqueue(pq, i, n->right);
		}
		else if(n->i->ratio == i->ratio)
		{
			printf("%f is equal to %f, checking profit\n", n->i->ratio, i->ratio);
			printf("profits are %" PRIu64 " and %" PRIu64 "\n", n->i->profit, i->profit);
			if(n->i->profit < i->profit)
			{
				printf("%" PRIu64 "is less than %" PRIu64 ", going left\n", n->i->profit, i->profit);
				n->left = _enqueue(pq, i, n->left);
			}
			else if(n->i->profit > i->profit)
			{
				printf("%" PRIu64 "is greater than %" PRIu64 ", going right\n", n->i->profit, i->profit);
				n->right = _enqueue(pq, i, n->right);
			}
			else if(n->i->profit == i->profit)
			{
				printf("profits are the same just go to the left fuck it\n");
				n->left = _enqueue(pq, i, n->left);
			}
		}
		return n;
	}
}

void enqueue(pqueue* pq, item* i)
{
	pq->root = _enqueue(pq, i, pq->root);
	return;
}

item
_dequeue(pqueue* pq, node* n)
{
	if(n == NULL)
		return nullitem;
	if(n->right != NULL)
		return _dequeue(pq, n->right);
	if(n->left != NULL)
		return _dequeue(pq, n->left);
	item i;
	printf("copying item %s\n", n->i->name);
	memcpy(&i, n->i, sizeof(item));
	printf("copied %s\n", i.name);
	printf("freeing node %s\n", i.name);
	free(n);
	return i;
}

item
dequeue(pqueue* pq)
{
	return _dequeue(pq, pq->root);
}
