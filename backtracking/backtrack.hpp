#ifndef _BACKTRACK_HPP_
#define _BACKTRACK_HPP_

#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>

typedef struct item_t {
	std::uint64_t profit;
	std::uint64_t weight;
	std::string name;
} item_t;

typedef struct node_t {
	item_t i;
	node_t* left;
	node_t* right;
	
	node_t()
	{
		i.profit = 0;
		i.weight = 0;
		i.name = "";
		left = nullptr;
		right = nullptr;
	}
} node_t;

class Backtrack {
	private:
	node_t* root;
	node_t* pos;
	std::uint64_t n, W, curw, maxp;
	item_t* items;
	std::uint64_t* weights;
	std::uint64_t* profits;
	std::string* include;
	
	public:
	Backtrack();
	void checknode(node_t& n);
	bool promising(std::uint64_t i);
	void knapsack(std::uint64_t i);
};

#endif