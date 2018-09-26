#include "main.hpp"

void
usage(void)
{
	printf("knapsack [filename]\n");
	return;
}

void
writesolfile(struct knapsack* ksack)
{
	
	return;
}

uint64_t
initpq(pqueue* pq, std::ifstream* fd)
{
	uint64_t value, weight, capacity, size;
	char name[64];
	item** items;

	value = weight = capacity = size = 0;
	*fd >> size;
	*fd >> capacity;
	pq->setSize(size);
	printf("number of items is %" PRIu64 "\n", pq->getSize());
	items = new item*;
	printf("allocated space on stack for items\n");
	for(uint64_t i = 0; i < pq->getSize(); i++)
	{
		items[i] = new item();
		*fd >> name;
		*fd >> value;
		*fd >> weight;
		strcpy(items[i]->name, name);
		items[i]->profit = value;
		items[i]->weight = weight;
		/* should this be a cast? */
		items[i]->ratio = (double) value / (double) weight;
		memset(&name, 0, 64 * sizeof(char));
	}
	printf("added 10000 items\n");
	printf("out of loop pqsize is %" PRIu64 "\n", pq->getSize());
	for(uint64_t i = 0; i < pq->getSize(); i++)
	{
		printf("calling enqueue on item %s at iteration %" PRIu64 ", less than %" PRIu64 "\n", items[i]->name, i, pq->getSize());
		pq->enqueue(items[i]);
		printf("enqueue called\n");
	}
	return capacity;
}

void
steal(struct pqueue* pq, struct knapsack* ksack)
{
	struct item i;
	
	i = nullitem;
	while(ksack->capacity >= 0)
	{
		i = pq->dequeue();
		printf("adding item %s %" PRIu64 " %" PRIu64 "\n",
				   i.name, i.profit, i.weight);
			ksack->sol_items[ksack->sol_item_num] = i;
			ksack->sol_item_num++;
			ksack->sol_profit += i.profit;
			ksack->sol_weight += i.weight;
			ksack->capacity -= i.weight;
			std::cout << "capcity is now " << ksack->capacity << std::endl;
	}
	writesolfile(ksack);
	return;
}

int
main(int argc, const char* argv[])
{
	std::string filename;
	std::ifstream fd;
	struct pqueue* pq;
	struct knapsack* joulethief;
	struct item** items;

	items = NULL;
	if(argc == 1 || argc > 2)
	{
		usage();
		exit(0);
	}
	srand((uint32_t)time(NULL));
	filename = argv[1];
	pq = new pqueue();
	joulethief = new knapsack();
	fd.open(filename, std::ios::in);
	joulethief->capacity = initpq(pq, &fd);
	std::cout << "got capacity " << joulethief->capacity << std::endl;
	steal(pq, joulethief);
	std::cout << "freeing data" << std::endl;
	fd.close();
	delete pq;
	exit(0);
}
