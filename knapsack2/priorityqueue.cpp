#include "priorityqueue.hpp"

int
enqueue(pqueue* pq, item* i)
{
	node *pos, *n;
	
	pos = pq->front;
	n = (node*) calloc(1, sizeof(node));
	n->i = i;
	n->next = NULL;
	if(pq->front == NULL)
	{
		pq->front = n;
		return 0;
	}
	while(n->i->ratio < pos->i->ratio)
	{
		if(pos->next != NULL)
		{
			pos = pos->next;
		}
		else
		{
			pos->next = n;
			return 0;
		}
	}
	/* in the case where the ratios are equal,
	 * prioritize the node with the higher value */
	if(n->i->ratio == pos->i->ratio)
	{
		
	}
	return 0;
}

item*
dequeue(pqueue* pq)
{
	item* ret;
	if(pq->front == NULL)
		return NULL;
	ret = pq->front->i;
	pq->front = pq->front->next;
	pq->size--;
	return ret;
}
