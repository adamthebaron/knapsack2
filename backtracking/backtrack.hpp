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
} item;

typedef struct node_t {
	item i;
	node* left;
	node* right;
	
	node()
	{
		i.profit = 0;
		i.weight = 0;
		i.name = "";
		left = nullptr;
		right = nullptr;
	}
} node;

class Backtrack {
	private:
	node* root;
	node* pos;
	std::uint64_t n, W, curw, maxp;
	item* items;
	std::uint64_t* weights;
	std::uint64_t* profits;
	
	
	public:
	Backtrack();
	void checknode(node& n);
	bool promising(std::uint64_t i);
	void knapsack(std::uint64_t i, 
				  std::uint64_t profit, 
				  std::uint64_t weight);
};

#endif