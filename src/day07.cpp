

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

int finish_time(const char & c){
	return (int) c - 4;
}

int main(){

	std::vector<std::string> input(get_lines<std::string>("day07-test.txt"));

	std::map <char, std::vector<char>> step_map;
	std::vector<char> performed_steps;


	// Creates a map of steps to a vector of the steps which needs to be complete 
	// before the step can be performed

	for(auto i : input){
		step_map[i[36]].push_back(i[5]);
		step_map[i[5]];
	}

	while(!step_map.empty()){

		// Find available step, perform it, then erase it from the list of remaining steps
		auto it = std::find_if(step_map.begin(), step_map.end(),[](std::pair<char,std::vector<char>> p){
				return p.second.empty();
			});
		performed_steps.push_back(it->first);
		step_map.erase(it);


		// Remove performed step from list of conditional steps in step map
		for(auto & kvp : step_map){
			for(const auto & step : performed_steps){
				auto it2 = std::find(kvp.second.begin(),kvp.second.end(),step);
				if( it2 != kvp.second.end())
					kvp.second.erase(it2);
			}
		}
	}


	// for(auto steps : performed_steps){
	// 	std::cout << steps;
	// }


	
	// Repeat the above process, but this time need to find all steps that can be performed rather
	// than just first alphabetically


	int available_workers = 0;
	std::map<char, int> job_complete_time;

	//if available workers
	// Start all available jobs, keep record of time when job will be complete
	// If no jobs are available, or no workers are available, progress time to point when a job is complete, then rechecker

	//

	std::map <char, std::vector<char>> step_map2;
	std::vector<char> performed_steps2;

	for(auto i : input){
		step_map2[i[36]].push_back(i[5]);
		step_map2[i[5]];
	}

	int check = 0;
	int time = 0;


	// while(!step_map2.empty()){



	// 	check += 1;
	// 	if(check > 200) break;
	// }

	for(auto step : step_map2){
		if(step.second.size() == 0){
		std::cout << step.first << "\n";
		std::cout << step.second.size() << "\n";

		}
	}

		// auto it = std::find_if(step_map2.begin(), step_map2.end(),[](std::pair<char,std::vector<char>> p){
		// 		return p.second.empty();
		// 	});

	// while(!step_map2.empty()){

	// 	// Find available step, perform it, then erase it from the list of remaining steps
	// 	auto it = std::find_if(step_map2.begin(), step_map2.end(),[](std::pair<char,std::vector<char>> p){
	// 			return p.second.empty();
	// 		});
	// 	performed_steps2.push_back(it->first);
	// 	step_map2.erase(it);


	// 	// Remove performed step from list of conditional steps in step map
	// 	for(auto & kvp : step_map2){
	// 		for(const auto & step : performed_steps2){
	// 			auto it2 = std::find(kvp.second.begin(),kvp.second.end(),step);
	// 			if( it2 != kvp.second.end())
	// 				kvp.second.erase(it2);
	// 		}
	// 	}
	// }

	// for(auto steps : performed_steps2){
	// 	std::cout << steps;
	// }
	std::cout << "The end\n";


	return 0;
}


