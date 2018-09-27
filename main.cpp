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
	std::cout << ksack->sol_item_num << std::endl;
	std::cout << ksack->sol_weight << std::endl;
	std::cout << ksack->sol_profit << std::endl;
	for(uint64_t i = 0; i < ksack->sol_item_num; i++)
	{
		std::cout << ksack->sol_items[i]->name << " " << ksack->sol_items[i]->profit << " " << ksack->sol_items[i]->weight << std::endl;
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
	items = new item*[size];
	for(uint64_t i = 0; i < size; i++)
	{
		//std::cout << "iteration " << i << std::endl;
		items[i] = new item();
		*fd >> items[i]->name;
		*fd >> items[i]->profit;
		*fd >> items[i]->weight;
		/* should this be a cast? */
		items[i]->ratio = (double) items[i]->profit / (double) items[i]->weight;
		//std::cout<< "added item ";
		//items[i]->print();
	}
	for(uint64_t i = 0; i < size; i++)
	{
		pq->enqueue(items[i]);
	}
	//pq->traversal();
	return capacity;
}

void
steal(struct pqueue* pq, struct knapsack* ksack)
{
	item* i;

	while(ksack->capacity >= 0)
	{
		i = pq->dequeue();
		//std::cout << "from dequeue we got ";
		//i->print();
		ksack->capacity -= i->weight;
		if(ksack->capacity <= 0)
			break;
		ksack->sol_items[ksack->sol_item_num] = i;
		ksack->sol_item_num++;
		ksack->sol_profit += i->profit;
		ksack->sol_weight += i->weight;
		//std::cout << "knapsack is now ";
		//ksack->string();
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
