

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

	std::vector<std::string> input(get_lines<std::string>("day07.txt"));

	std::map <char, std::vector<char>> step_map;
	std::vector<char> performed_steps;


	// Creates a map of steps to a vector of the steps which needs to be complete 
	// before the step can be performed

	// for(auto i : input){
	// 	step_map[i[36]].push_back(i[5]);
	// 	step_map[i[5]];
	// }

	// while(!step_map.empty()){

	// 	// Find available step, perform it, then erase it from the list of remaining steps
	// 	auto it = std::find_if(step_map.begin(), step_map.end(),[](std::pair<char,std::vector<char>> p){
	// 			return p.second.empty();
	// 		});
	// 	performed_steps.push_back(it->first);
	// 	step_map.erase(it);


	// 	// Remove performed step from list of conditional steps in step map
	// 	for(auto & kvp : step_map){
	// 		for(const auto & step : performed_steps){
	// 			auto it2 = std::find(kvp.second.begin(),kvp.second.end(),step);
	// 			if( it2 != kvp.second.end())
	// 				kvp.second.erase(it2);
	// 		}
	// 	}
	// }


	// for(auto steps : performed_steps){
	// 	std::cout << steps;
	// }




	// Part 2
	

	// time = 0;
	// workers_used = 0

	// vector<steps, time_finishest> steps_complete_time

	// while(steps_left_to_do){

	// 	while(steps_available_to_do and workers < 4){
	// 		workers_used += 1;
	// 		add_step_to_queue
	// 	}

	// 	progress_time_to_next_step_complete;
	// 	remove_compelted_step_form_list_of_requirements;
		
	// }

	std::string order = "";
	int time = 0;
	int workers_used = 0;
	int max_workers = 5;

	std::vector<std::pair<char, int>> step_complete_time;

	for(auto i : input){
		step_map[i[36]].push_back(i[5]);
		step_map[i[5]];
	}


	int tick = 0;

	while(!step_map.empty()){


		for(auto steps : step_map){
			std::cout << steps.first << ": ";
			for(auto s : steps.second){
				std::cout << s << ", ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
		auto available_step = std::find_if(step_map.begin(), step_map.end(),[](std::pair<char,std::vector<char>> p){
				return p.second.empty();
			});

		std::cout << "Current time " << time << "\n";
		while(available_step != step_map.end() && workers_used != max_workers){
			std::cout << "Beginning step " << available_step->first <<
			", Duration : " << finish_time(available_step->first) << ", " << 
			 " which will be finished at " << time + finish_time(available_step->first)  -1<< "\n";
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
		order = order + step_complete_time[0].first;
		workers_used--;
		for(auto & kvp : step_map){
			auto it2 = std::find(kvp.second.begin(), kvp.second.end(), step_complete_time[0].first);
			if( it2 != kvp.second.end())
				kvp.second.erase(it2);
		}

		step_complete_time.erase(step_complete_time.begin());

		tick++;

	}



	// for(auto p : step_complete_time){
	// 	std::cout << p.first << ", " << p.second << "\n";
	// }
	std::cout << order << "\n";

	std::cout << "Time : " << time << "\n";


	
	// std::vector<int> vec;
	// vec.push_back(5);
	// vec.push_back(1);
	// vec.push_back(2);
	// vec.push_back(3);
	// vec.push_back(1);
	// vec.push_back(3);

	// for(auto v : vec){
	// 	std::cout << v << "\n";
	// }

	// std::cout << "\n";

	// vec.erase(vec.begin());
	// for(auto v : vec){
	// 	std::cout << v << "\n";
	// }


	// std::vector<int>::iterator i = std::find_if(vec.begin(), vec.end(),[](int a){return a > 2;});

	// while(i != vec.end()){
	// 	vec.erase(i);
	// 	i = std::find_if(vec.begin(), vec.end(),[](int a){return a > 2;});
	// }


	// for(auto v : vec){
	// 	std::cout << v << "\n";
	// }
	// while(std::find_if(vec.begin(), vec.end(),[](int a){return a == >2;}) != vec.end();)

	// auto it = std::find_if(vec.begin(), vec.end(),[](int a){
	// 			return a == 4;
	// 		});
	// std::cout << *vec.end() << "\n";
	// std::cout << *it << "\n";

	// if(vec.end() == it){
	// 	std::cout << "Boop!\n";
	// }

	// int available_workers = 0;
	// std::map<char, int> job_complete_time;

	// //if available workers
	// // Start all available jobs, keep record of time when job will be complete
	// // If no jobs are available, or no workers are available, progress time to point when a job is complete, then rechecker

	// //

	// std::map <char, std::vector<char>> step_map2;
	// std::vector<char> performed_steps2;

	// for(auto i : input){
	// 	step_map2[i[36]].push_back(i[5]);
	// 	step_map2[i[5]];
	// }u

	// int check = 0;
	// int time = 0;

	// // A vector a steps and the time they will be complete
	// std::vector<std::pair<char, int>> step_complete;


	// while(check < 200){
	// 	// !step_map2.empty()
	// 	// check += 1;
	// }

	// for(auto step : step_map2){
	// 	if(step.second.size() == 0){
	// 	std::cout << step.first << "\n";
	// 	std::cout << step.second.size() << "\n";

	// 	}
	// }

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


