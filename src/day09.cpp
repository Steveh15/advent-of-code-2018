
#include <list>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

#include "include/get_input.hpp"




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


uint64_t marble_game(int players, uint64_t marbles){

	std::list<uint64_t> marble_circle;
	std::map<int, uint64_t> player_score;
	std::list<uint64_t>::iterator current_marble = marble_circle.begin();

	marble_circle.push_back(0);

	int current_player = 1;
	int max_players = players;
	uint64_t max_marble = marbles;
	
	for(uint64_t i = 1; i <= max_marble; i++){
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

	auto max_score_it = max_element(player_score.begin(), player_score.end(), []( std::pair<int,uint64_t> a, std::pair<int,uint64_t> b ){
		return a.second < b.second;
	});
	return max_score_it->second;
}




int main(){


	std::cout << "Max score : " << marble_game(459, 71320) << "\n";
	std::cout << "Max score : " << marble_game(459, 71320*100) << "\n";

	return 0;
}


/*
	Things learnt
		1) Iterators become invalid when the container they are pointed to changes
		2) <list> is a linked list, <vector> is contiguous memory. This produces several differences, the key
			one here being that it is much quicker to do insertions on a linked list, so code needed to change to use lists instead
		3) int can have a max size of ~2.3 billion, so need to use something large on occasion
		4) Can use ints in if statements, 0 = false, anything else = true. Can utilise this in while statements, as loop will terminate when reaches 0.

*/

