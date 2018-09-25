#include "main.h"

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
	FILE* fd;

	if((fd = fopen(filename, "w")) == NULL)
	{
		fprintf(stderr, "error creating test file: %s\n", strerror(errno));
		exit(1);
	}
	if(fprintf(fd, "%" PRIu64 " %" PRIu64 "\n", num, weight) < 0)
		return 1;
	for(uint64_t i = 0; i < num; i++)
		if(fprintf(fd, "item%" PRIu64 " %" PRIu64 " %" PRIu64 "\n", i,
				   genrand(num), genrand(num)) < 0)
			return 1;
	return 0;
}

void
writesolfile(struct knapsack* ksack)
{
	
	return;
}

uint64_t
initpq(struct pqueue* pq, FILE* fd, struct item** items)
{
	uint64_t value, weight, capacity;
	char name[64];

	value = weight = capacity = 0;
	fscanf(fd, "%" PRIu64 " %" PRIu64, &(pq->size), &capacity);
	printf("number of items is %" PRIu64 "\n", pq->size);
	items = calloc(1, sizeof(struct item*));
	printf("allocated space on stack for items\n");
	for(uint64_t i = 0; i < pq->size; i++)
	{
		if((items[i] = calloc(1, sizeof(struct item))) == NULL)
			fprintf(stderr, "error allocating space for item %" PRIu64 "\n", i);
		fscanf(fd, "%s %" PRIu64 " %" PRIu64, &name, &value, &weight);
		//printf("checking item %s %" PRIu64 " %" PRIu64 "\n", name, value, weight);
		strcpy(items[i]->name, name);
		//printf("copying name %s\n", items[i]->name);
		items[i]->profit = value;
		//printf("copying value %" PRIu64 "\n", items[i]->profit);
		items[i]->weight = weight;
		//printf("copying weight %" PRIu64 "\n", items[i]->weight);
		/* should this be a cast? */
		items[i]->ratio = (double) value / (double) weight;
		//printf("copying ratio %f\n", items[i]->ratio);
		//printf("clearing name memory\n");
		memset(&name, 0, 64 * sizeof(char));
		//printf("cleared\n");
		//printf("added item %s %" PRIu64 " %" PRIu64 " %f\n", items[i]->name,
	//		   items[i]->profit, items[i]->weight, items[i]->ratio);
	}
	printf("added 10000 items\n");
	printf("out of loop pqsize is %" PRIu64 "\n", pq->size);
	for(uint64_t i = 0; i < pq->size; i++)
	{
		printf("calling enqueue on item %s at iteration %" PRIu64 ", less than %" PRIu64 "\n", items[i]->name, i, pq->size);
		enqueue(pq, items[i]);
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
		i = dequeue(pq);
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

void
freedata(struct pqueue* pq)
{
	freetree(pq->root);
	return;
}

int
main(int argc, const char* argv[])
{
	uint64_t nflag, wflag, opt;
	char* filename;
	FILE* fd;
	struct pqueue* pq;
	struct knapsack* joulethief;
	struct item** items;
	
	nflag = wflag = opt = 0;
	filename = NULL;
	fd = NULL;
	items = NULL;
	if(argc == 1)
	{
		usage();
		exit(0);
	}
	srand((uint32_t)time(NULL));
	if((pq = calloc(1, sizeof(struct pqueue))) == NULL)
		fprintf(stderr, "error allocating priority queue: %s\n", strerror(errno));
	memset(pq, 0, sizeof(struct pqueue));
	if((joulethief = calloc(1, sizeof(struct knapsack))) == NULL)
		fprintf(stderr, "error allocating knapsack: %s\n", strerror(errno));
	memset(joulethief, 0, sizeof(struct knapsack));
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
		fprintf(stderr, "specify both a number and weight to generate a file\n");
		exit(1);
	}
	if(nflag && wflag)
	{
		if(genfile(nflag, wflag))
		{
			fprintf(stderr, "error writing to test file\n");
			exit(1);
		}
		exit(0);
	}
	if(filename != NULL)
	{
		if((fd = fopen(filename, "r")) == NULL)
		{
			fprintf(stderr, "error opening %s\n", filename);
			exit(1);
		}
		joulethief->capacity = initpq(pq, fd, items);
		steal(pq, joulethief);
	}
	fclose(fd);
	printf("freeing item space\n");
	for(uint64_t i = 0; i < pq->size; i++)
		free(items[i]);
	free(items);
	printf("freeing bst\n");
	freedata(pq);
	printf("freeing knapsack\n");
	free(joulethief);
	printf("freeing pq\n");
	free(pq);
	exit(0);
}
