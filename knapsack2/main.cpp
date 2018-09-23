#include "main.hpp"
#include "priorityqueue.hpp"

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

int
initpq(pqueue* pq, FILE* fd)
{
	
}

int
main(int argc, const char* argv[])
{
	uint64_t nflag, wflag, opt;
	char* filename;
	FILE* fd;
	pqueue* pq;
	knapsack* joulethief;
	
	srand((uint32_t)time(NULL));
	nflag = wflag = opt = 0;
	filename = NULL;
	fd = NULL;
	if((pq = (pqueue*) calloc(1, sizeof(pqueue))) == NULL)
	{
		fprintf(stderr, "error allocating priority queue: %s\n", strerror(errno));
	}
	if((joulethief = (knapsack*) calloc(1, sizeof(knapsack))) == NULL)
	{
		fprintf(stderr, "error allocating knapsack: %s\n", strerror(errno));
	}
	if(argc == 1)
	{
		usage();
		exit(0);
	}
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
	}
	if(filename != NULL)
	{
		if((fd = fopen(filename, "r")) == NULL)
		{
			fprintf(stderr, "error opening %s\n", filename);
			exit(1);
		}
		initpq(pq, fd);
	}
	free(joulethief);
	free(pq);
	exit(0);
}
