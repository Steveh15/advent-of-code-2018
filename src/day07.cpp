

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

#include "include/get_input.hpp"

int main(){

	std::vector<std::string> input(get_lines<std::string>("day07.txt"));

	std::map <char, std::vector<char>> step_map;
	std::vector<char> current_steps;
	std::vector<char> performed_steps;


	for(auto i : input){
		step_map[i[5]].push_back(i[36]);
	}

	return 0;
}


