#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

void
usage(void)
{
	std::cout << "genfile [n] [w] [filename]" << std::endl;
	return;
}

uint64_t
genrand(uint64_t num)
{
	return rand() % num + 1;
}

void
genfile(uint64_t n, uint64_t w, std::string filename)
{
	std::ofstream fd;

	fd.open(filename, std::ios::out);
	fd << n << " " << w << std::endl;
	for(uint64_t i = 0; i < n; i++)
		fd << "item" << i << " " << genrand(n) << " " << genrand(w) << std::endl;
	return;
}

int
main(int argc, char* argv[])
{
	std::string filename;
	uint64_t n, w;

	n = w = 0;
	if(argc == 1 || argc > 3)
	{
		usage();
		exit(1);
	}
	n = strtoll(argv[1], NULL, 10);
	w = strtoll(argv[2], NULL, 10);
	filename = argv[3];
	std::cout << n << " " << w << " " << filename << std::endl;
	exit(0);
}