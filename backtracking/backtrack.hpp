#ifndef _BACKTRACK_HPP_
#define _BACKTRACK_HPP_

#include <cstdint>
#include <string>
#include <iostream>

#include "priorityqueue.hpp"

class Backtrack {
	private:
	pqueue pq;
	std::uint64_t n, W, curw, maxp;
	item* items;
	std::uint64_t* weights;
	std::uint64_t* profits;
	std::string* include;
	
	public:
	Backtrack();
	bool promising(std::uint64_t i);
	void knapsack(std::uint64_t i);
	void printSolution(void);
	bool setW(std::uint64_t w);
	void setn(std::uint64_t n);
	void enqueue(item* i);
	itemptr& top(void);
};

#endif