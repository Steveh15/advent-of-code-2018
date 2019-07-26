
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

#include "include/get_input.hpp"


// std::vector<int>::iterator rotate(const int & rotate, std::vector<int>::iterator it){
// 	return it;
// }




void rotate_current_marble(std::list<uint64_t>::iterator & current_marble, std::list<uint64_t> & marble_circle, int n){
	bool direction = true;
	if(n < 0){
		direction = false;
		n = -n;
	}
	if(direction){
		for(int i = 0; i < n; i ++){
			current_marble++;
			if(current_marble == marble_circle.end()){
				current_marble = marble_circle.begin();
			}
		}
	} else{
		for(int i = 0; i < n; i++){
			if(current_marble == marble_circle.begin()){
				current_marble = marble_circle.end();
			}
			current_marble--;			
		}
	}
}


int main(){




	std::list<uint64_t> marble_circle;
	std::map<int, uint64_t> player_score;

	// Do first couple of rounds manually
	marble_circle.push_back(0);
	marble_circle.push_back(1);

	std::list<uint64_t>::iterator current_marble = --marble_circle.end();

	int current_player = 2;
	int max_players = 30;
	uint64_t max_marble = 5807;

	max_players = 459;
	max_marble = 71320*100;
	
	for(uint64_t i = 2; i <= max_marble; i++){

		if( i % 23 == 0){
			rotate_current_marble(current_marble,marble_circle,-7);
			player_score[current_player] += i + *current_marble;
			current_marble = marble_circle.erase(current_marble);
		} else{
			rotate_current_marble(current_marble,marble_circle,2);
			current_marble = marble_circle.insert(current_marble,i);
		}

		if(++current_player > max_players) current_player = 1;
		
	}


	std::cout << "current_marble : " << *current_marble << "\n";

	uint64_t max_score = 0;
	int max_player = 0;
	for(auto s : player_score){
		std::cout << s.first << ", " << s.second << "\n";
		if(s.second > max_score) {
			max_score = s.second;
			max_player = s.first;
		}
	}

	//3168033673
	std::cout << "Max player : " << max_player << "\n";
	std::cout << "Max score : " << max_score << "\n";

return 0;
}


/*
	Things learnt
		1) Iterators become invalid when the container they are pointed to changes

*/

