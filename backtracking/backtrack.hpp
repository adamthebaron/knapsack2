#ifndef _BACKTRACK_HPP_
#define _BACKTRACK_HPP_

#include <cstdint>
#include <string>
#include <iostream>

#include "priorityqueue.hpp"

class Backtrack {
	private:
	
	public:
	std::uint64_t n, w, p, W, maxprofit, numbest;
	bool* include;
	bool* bestset;
	item* items;
	pqueue pq;
	Backtrack();
	bool promising(std::uint64_t& i, std::uint64_t& profit, 
									 std::uint64_t& weight);
	void knapsack(std::uint64_t& i, std::uint64_t& profit,
									std::uint64_t& weight);
	void printSolution(void);
	bool setW(std::uint64_t w);
	std::uint64_t getW(void);
	void setn(std::uint64_t n);
	std::uint64_t getn(void);
	void enqueue(item* i);
	itemptr& top(void);
};

#endif