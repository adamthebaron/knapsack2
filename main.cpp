#include "main.hpp"

void
usage(void)
{
	printf("knapsack [-h] [-n numitems] [-w weight] [-f file]\n");
	return;
}

uint64_t
genrand(uint64_t num)
{
	return rand() % num + 1;
}

int
genfile(uint64_t num, uint64_t weight)
{
	const char* filename = "./testfile";
	std::ofstream fd;

	fd.open(filename, std::ios::out);
	fd << num << " " << weight << std::endl;
	for(uint64_t i = 0; i < num; i++)
		fd << "item" << i << " " << genrand(num) << " " << genrand(num) << std::endl;
			return 1;
	return 0;
}

void
writesolfile(struct knapsack* ksack)
{
	
	return;
}

uint64_t
initpq(pqueue* pq, std::ifstream* fd, std::istringstream iss)
{
	uint64_t value, weight, capacity, size;
	char name[64];
	item** items;

	value = weight = capacity = size = 0;
	fd >> size >> capacity;
	pq->setSize(size);
	printf("number of items is %" PRIu64 "\n", pq->getSize());
	items = new item*;
	printf("allocated space on stack for items\n");
	for(uint64_t i = 0; i < pq->getSize(); i++)
	{
		items[i] = new item();
		fd->getline(name, value, weight);
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
		if(!strcmp(i.name, nullitem.name))
		{
			printf("no more items to check, you got everything\n");
			return;
		}
		if(i.weight < ksack->capacity)
		{
			printf("adding item %s %" PRIu64 " %" PRIu64 "\n",
				   i.name, i.profit, i.weight);
			ksack->sol_items[ksack->sol_item_num] = i;
			ksack->sol_item_num++;
			ksack->sol_profit += i.profit;
			ksack->sol_weight += i.weight;
			ksack->capacity -= i.weight;
		}
	}
	writesolfile(ksack);
	return;
}

void
freetree(struct node* n)
{
	if(n == NULL)
		return;
	printf("freeing node with data: %s %" PRIu64 " %" PRIu64 "\n",
		   n->i->name, n->i->profit, n->i->weight);
	freetree(n->left);
	freetree(n->right);
}

/*void
freedata(struct pqueue* pq)
{
	freetree(pq->root);
	return;
}*/

int
main(int argc, const char* argv[])
{
	uint64_t nflag, wflag, opt;
	std::string filename;
	std::fstream fd;
	std::istringstream iss;
	struct pqueue* pq;
	struct knapsack* joulethief;
	struct item** items;
	
	nflag = wflag = opt = 0;
	filename = "";
	items = NULL;
	if(argc == 1)
	{
		usage();
		exit(0);
	}
	srand((uint32_t)time(NULL));
	pq = new pqueue();
	joulethief = new knapsack();
	while((opt = getopt(argc, (char* const*)argv, "f:hn:w:")) != -1)
	{
		switch(opt)
		{
			case 'f':
				filename = optarg;
				break;
			case 'n':
				nflag = atoi(optarg);
				break;
			case 'w':
				wflag = atoi(optarg);
				break;
			case 'h':
			case '?':
			default:
				usage();
				exit(0);
		}
	}
	argc -= optind;
	argv += optind;
	if((nflag && !wflag) || (!nflag && wflag))
	{
		std::cerr <<  "specify both a number and weight to generate a file" << std::endl;
		exit(1);
	}
	if(nflag && wflag)
	{
		if(genfile(nflag, wflag))
		{
			std::cerr << "error writing test file" << std::endl;
			exit(1);
		}
		exit(0);
	}
	if(filename != "")
	{
		fd.open(filename, std::ios::in);
		joulethief->capacity = initpq(pq, &fd, iss);
		steal(pq, joulethief);
	}
	if(fd.is_open())
		fd.close();
	printf("freeing item space\n");
	for(uint64_t i = 0; i < pq->getSize(); i++)
		free(items[i]);
	free(items);
	printf("freeing bst\n");
	printf("freeing knapsack\n");
	free(joulethief);
	printf("freeing pq\n");
	delete pq;
	exit(0);
}
