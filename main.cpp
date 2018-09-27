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
	for(uint64_t i = 0; i < ksack->sol_item_num; i++)
	{
		std::cout << "item " << i << " is " << ksack->sol_items[i].name << " " << ksack->sol_items[i].ratio << std::endl;
	}
	std::cout << "solution profit " << ksack->sol_profit << std::endl;
	std::cout << "solution weight " << ksack->sol_weight << std::endl;
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
	printf("number of items is %" PRIu64 "\n", pq->getSize());
	items = new item*[capacity];
	printf("allocated space on stack for items\n");
	for(uint64_t i = 0; i < pq->getSize(); i++)
	{
		items[i] = new item();
		*fd >> items[i]->name;
		*fd >> items[i]->profit;
		*fd >> items[i]->weight;
		/* should this be a cast? */
		items[i]->ratio = (double) items[i]->profit / (double) items[i]->weight;
		std::cout << "added item " << items[i]->name << " of profit " << items[i]->profit << " and weight " << items[i]->weight << " and ratio " << items[i]->ratio << std::endl;
	}
	std::cout << "added " << pq->getSize() << " items" << std::endl;
	for(uint64_t i = 0; i < pq->getSize(); i++)
	{
		std::cout << "calling enqueue on item " << items[i]->name << " at iteration " << i << std::endl;
		pq->enqueue(items[i]);
		std::cout << "called enqueue" << std::endl;
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
		std::cout << "checking item " << i.name << " " << i.profit << " " << i.weight << " " << i.ratio << std::endl;
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
