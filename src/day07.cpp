

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

	std::vector<std::string> input(get_lines<std::string>("day07-test.txt"));

	std::map <char, std::vector<char>> step_map;
	std::vector<char> current_steps;
	std::vector<char> performed_steps;


	for(auto i : input){
		step_map[i[36]].push_back(i[5]);
		step_map[i[36]];
		step_map[i[5]];
	}


	// for(auto & m : step_map){
	// 	std::cout << m.first << " : ";
	// 	for(auto l : m.second){
	// 		std::cout << l << ", ";
	// 	}
	// 	std::cout << "\n";
	// }


	//
	//	1 loop
	//


	while(!step_map.empty()){

		printCurrent(step_map);

		auto it = std::find_if(step_map.begin(), step_map.end(),[](std::pair<char,std::vector<char>> p){
			return p.second.empty();
		});

		// 1 and 2)
		while(  it != step_map.end()){
			current_steps.push_back(it->first);
			// step_map.erase(it);
			it = std::find_if(step_map.begin(), step_map.end(),[](std::pair<char,std::vector<char>> p){
				return p.second.empty();
			});
		}

		// 3)
		std::sort(current_steps.begin(), current_steps.end());
		performed_steps.push_back(current_steps[0]);
		// auto delete_find = step_map.find(current_steps[0]);
		// step_map.erase(delete_find);
		// for(auto & m : current_steps){
		// 	performed_steps.push_back(m);
		// }

		current_steps.clear();

		// 3)
		for(auto & kvp : step_map){
			for(const auto & step : performed_steps){
				auto it2 = std::find(kvp.second.begin(),kvp.second.end(),step);
				if( it2 != kvp.second.end()){
					kvp.second.erase(it2);
				}
			}
		}


	}



	//
	//	2 loop
	//



	for(auto steps : performed_steps){
		std::cout << steps;
	}
	std::cout << "\nCABDFE is correct";
	// 1) Find steps with no predecessors, store them and delete them from the list of steps to be performed
	// 2) Delete them from the instruction list
	// 3) Delete them from the precursor steps
	// 4) Sort them and then perform them
	// Repeat

	


	return 0;
}


