#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

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
main(int argc, char** argv)
{
	std::string filename;
	uint64_t n, w;

	n = w = 0;

	exit(0);
}