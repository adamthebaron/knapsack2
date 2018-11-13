#ifndef _BACKTRACK_HPP_
#define _BACKTRACK_HPP_

#include <cstdint>
#include <string>
#include <iostream>

#include "priorityqueue.hpp"

static std::string YES = "yes";
static std::string NO = "no";

class Backtrack {
	private:
	
	public:
	std::uint64_t n, w, p, W, maxprofit, numbest;
	std::string** include;
	std::string** bestset;
	item* items;
	pqueue pq;
	Backtrack();
	bool promising(std::uint64_t i);
	void knapsack(std::uint64_t i);
	void printSolution(void);
	bool setW(std::uint64_t w);
	std::uint64_t getW(void);
	void setn(std::uint64_t n);
	std::uint64_t getn(void);
	void enqueue(item* i);
	itemptr& top(void);
};

#endif