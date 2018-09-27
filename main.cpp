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
	std::cout << ksack->sol_profit << std::endl;
	std::cout << ksack->sol_weight << std::endl;
	for(uint64_t i = 0; i < ksack->sol_item_num; i++)
	{
		std::cout << ksack->sol_items[i].name << " " << ksack->sol_items[i].ratio << std::endl;
	}
	return;
}

uint64_t
initpq(pqueue* pq, std::ifstream* fd)
{
	uint64_t capacity, size;
	char name[64];
	item** items;

	capacity = size = 0;
	*fd >> size;
	*fd >> capacity;
	pq->setSize(size);
	items = new item*[capacity];
	for(uint64_t i = 0; i < pq->getSize(); i++)
	{
		items[i] = new item();
		*fd >> items[i]->name;
		*fd >> items[i]->profit;
		*fd >> items[i]->weight;
		/* should this be a cast? */
		items[i]->ratio = (double) items[i]->profit / (double) items[i]->weight;
	}
	for(uint64_t i = 0; i < pq->getSize(); i++)
	{
		pq->enqueue(items[i]);
	}
	return capacity;
}

void
steal(struct pqueue* pq, struct knapsack* ksack)
{
	item i;

	while(ksack->capacity >= 0)
	{
		i = pq->dequeue();
		ksack->sol_items[ksack->sol_item_num] = i;
		ksack->sol_item_num++;
		ksack->sol_profit += i.profit;
		ksack->sol_weight += i.weight;
		ksack->capacity -= i.weight;
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
	steal(pq, joulethief);
	fd.close();
	delete pq;
	exit(0);
}
