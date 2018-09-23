#include "main.hpp"

struct
node
{
	item* i;
	node* next;
};

struct
pqueue
{
	node* front;
	int (*enqueue) (pqueue*, item);
	item* (*dequeue) (pqueue*);
};

int
enqueue(pqueue* pq, item i)
{
	return 0;
}

item*
dequeue(pqueue* pq)
{
	item* ret;
	if(pq->front == NULL)
	{
		return NULL;
	}
	ret = pq->front->i;
	pq->front = pq->front->next;
	return ret;
}
