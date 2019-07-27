

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

#include "include/get_input.hpp"


int finish_time(const char & c){
	return (int) c - 4;
}

int main(){

	std::vector<std::string> input(get_lines<std::string>("day07.txt"));

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

	std::cout << "Part one : ";
	for(auto steps : performed_steps){
		std::cout << steps;
	}
	std::cout << "\n";




	// Part 2
	



	int time = 0;
	int workers_used = 0;
	int max_workers = 5;

	std::vector<std::pair<char, int>> step_complete_time;

	step_map.clear();
	for(auto i : input){
		step_map[i[36]].push_back(i[5]);
		step_map[i[5]];
	}


	while(!step_map.empty()){


		auto available_step = std::find_if(step_map.begin(), step_map.end(),[](std::pair<char,std::vector<char>> p){
				return p.second.empty();
			});

		// Start all available steps
		while(available_step != step_map.end() && workers_used != max_workers){
			step_complete_time.push_back(std::pair<char,int>(available_step->first,time + finish_time(available_step->first)));
			step_map.erase(available_step);

			workers_used++;
			available_step = std::find_if(step_map.begin(), step_map.end(),[](std::pair<char,std::vector<char>> p){
				return p.second.empty();
			});
		}


		// No more steps can be started, so advance to next time point and remove blocking steps
		std::sort(step_complete_time.begin(), step_complete_time.end(), [](const std::pair<char,int> a, const std::pair<char,int> b){
			return a.second < b.second;
		});
		time = step_complete_time[0].second;
		workers_used--;
		for(auto & kvp : step_map){
			auto it2 = std::find(kvp.second.begin(), kvp.second.end(), step_complete_time[0].first);
			if( it2 != kvp.second.end())
				kvp.second.erase(it2);
		}

		step_complete_time.erase(step_complete_time.begin());

	}



	std::cout << "Part two : " << time << "\n";


	return 0;
}


