#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <numeric>
#include "include/get_input.hpp"


int PartTwo(const std::vector<int> & changes){

	std::vector<int>::const_iterator it = changes.begin();
	std::map<int,int> freqs;
	int sum  = 0 ;

	while(true){
		sum += *it++;
		freqs[sum] += 1;

		if(freqs[sum] == 2)
			return sum;
		
		if(it == changes.end())
			it = changes.begin();
	}

	return -1; // No solution found
}

// Use sets to simplify code
int PartTwoAlt(const std::vector<int> & changes){

	std::set<int> sums;
	int sum = 0;
	while(true){
		for(const auto val : changes){
			sum += val;
			if(!sums.insert(sum).second)
				return sum;
		}
	}

}


int main(){

	std::vector<int> input = get_lines<int>("day01.txt");

	auto part1 = std::accumulate(std::begin(input), std::end(input), 0);
    std::cout << "Part 1 answer: " << part1 << '\n';

	// std::cout << "Part 2 answer : " << PartTwo(input) << "\n";
	std::cout << "Part 2 answer : " << PartTwoAlt(input) << "\n";

}
	/*
		Things learned
			std::accumulate can be used to calculate statistics like the mean
			Alternate ways of looping through a vector multiple times
				1) put a for loop in a while loop
				2) Use iterators to reset to beginning once end is reached
			Sets can tell you when you're trying to add an object which is already in there

*/