

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

#include "include/get_input.hpp"


void printCurrent(std::map <char, std::vector<char>> step_map){
	for(auto & m : step_map){
		std::cout << m.first << " : ";
		for(auto l : m.second){
			std::cout << l << ", ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int main(){

	std::vector<std::string> input(get_lines<std::string>("day07.txt"));

	std::map <char, std::vector<char>> step_map;
	std::vector<char> current_steps;
	std::vector<char> performed_steps;


	for(auto i : input){
		step_map[i[36]].push_back(i[5]);
		step_map[i[36]];
		step_map[i[5]];
	}

	while(!step_map.empty()){

		auto it = std::find_if(step_map.begin(), step_map.end(),[](std::pair<char,std::vector<char>> p){
				return p.second.empty();
			});

		performed_steps.push_back(it->first);

		for(auto & kvp : step_map){
			for(const auto & step : performed_steps){
				auto it2 = std::find(kvp.second.begin(),kvp.second.end(),step);
				if( it2 != kvp.second.end())
					kvp.second.erase(it2);
				
			}
		}

		step_map.erase(it);
	}


	for(auto steps : performed_steps){
		std::cout << steps;
	}


	std::map<char, int> finish_time;



	return 0;
}


