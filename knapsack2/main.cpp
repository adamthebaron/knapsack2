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

uint64_t
initpq(pqueue* pq, FILE* fd, item** items)
{
	uint64_t value, weight, capacity;
	char* name;

	name = (char*) calloc(64, sizeof(char));
	items = (item**) calloc(1, sizeof(item*));
	memset(name, 0, 64 * sizeof(char));
	value = weight = capacity = 0;
	pq->front = (node*) calloc(1, sizeof(node));
	pq->front->i = (item*) calloc(1, sizeof(item));
	fscanf(fd, "%" PRIu64 " %" PRIu64, &(pq->size), &capacity);
	printf("number of items is %" PRIu64 "\n", pq->size);
	for(uint64_t i = 0; i < pq->size; i++)
	{
		fscanf(fd, "%s %" PRIu64 " %" PRIu64, name, &value, &weight);
		printf("checking item %s %" PRIu64 " %" PRIu64 "\n", name, value, weight);
		items[i] = (item*) calloc(1, sizeof(item));
		strcpy(items[i]->name, name);
		items[i]->profit = value;
		items[i]->weight = weight;
		/* should this be a cast? */
		items[i]->ratio = (double) value / (double) weight;
		memset(name, 0, 64 * sizeof(char));
		printf("added item %s %" PRIu64 " %" PRIu64 " %f\n", items[i]->name,
			   items[i]->profit, items[i]->weight, items[i]->ratio);
	}
	for(uint64_t i = 0; i < pq->size; i++)
		enqueue(pq, items[i]);
	free(name);
	return capacity;
}

int
steal(pqueue* pq, knapsack* ksack)
{
	return 0;
}

void
freedata(item** items, pqueue* pq)
{
	node *pos, *next;
	
	next = NULL;
	pos = pq->front;
	for(uint64_t i = 0; i < pq->size; i++)
		free(items[i]);
	free(items);
	while(pos->next != NULL)
	{
		next = pos->next;
		free(pos);
		pos = next;
	}
	return;
}

int
main(int argc, const char* argv[])
{
	uint64_t nflag, wflag, opt;
	char* filename;
	FILE* fd;
	pqueue* pq;
	item** items;
	knapsack* joulethief;
	
	nflag = wflag = opt = 0;
	filename = NULL;
	items = NULL;
	fd = NULL;
	if(argc == 1)
	{
		usage();
		exit(0);
	}
	srand((uint32_t)time(NULL));
	if((pq = (pqueue*) calloc(1, sizeof(pqueue))) == NULL)
		fprintf(stderr, "error allocating priority queue: %s\n", strerror(errno));
	if((joulethief = (knapsack*) calloc(1, sizeof(knapsack))) == NULL)
		fprintf(stderr, "error allocating knapsack: %s\n", strerror(errno));
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
	freedata(items, pq);
	free(joulethief);
	free(pq);
	exit(0);
}
