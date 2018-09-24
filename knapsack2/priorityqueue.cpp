#include "priorityqueue.hpp"

int
enqueue(pqueue* pq, item* i)
{
	node *pos, *newitem;
	
	pos = pq->front;
	/*
	newitem = (node*) calloc(1, sizeof(node));
	newitem->i = i;
	newitem->next = NULL;
	while(newitem->i->ratio < pos->i->ratio)
	{
		pos = pos->next;
	}
	*/
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
