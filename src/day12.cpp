#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>

#include "include/get_input.hpp"

struct Evolution
{
	std::string prior_states;
	char new_state;	
};



// std::ostream& operator<<(std::ostream& os, const Evolution& evo)
// {
//     os << "x : [" << point.x.x << ", " << point.x.y << "], v : [" << point.v.x << ", " << point.v.y << "]";
//     return os;
// }


// ...## => #
std::istream& operator>>(std::istream& is, Evolution& evo)
{
	char * buffer = new char[5];
	is.read(buffer,5);
	std::string newstr(buffer);

	is.read(buffer,5);
	char newc = buffer[4];
	Evolution ev = {newstr,newc};
	evo = ev;
	std::getline(is,newstr);

	return is;
}


std::string UpdateState(const  std::string & old_state, const std::unordered_map<std::string, char> & evolution_map){

	std::string  current_state;
	std::string  new_state = old_state;

	for(int i = 0; i < old_state.size() - 4; i++){
		current_state.clear();

		for(int j = i; j < i + 5; j++){
			current_state += old_state[j];
		}
		auto it = evolution_map.find(current_state);
		

		if(it == evolution_map.end()){
			new_state[i+2] = '.';
		} else{
			new_state[i+2] = it->second;
		}
	}

	return new_state;
}



int main()
{

	std::string old_state = "###..###....####.###...#..#...##...#..#....#.##.##.#..#.#..##.#####..######....#....##..#...#...#.#";
	std::string new_state;
	

	old_state = "........................................" + old_state + "........................................................................";
	new_state = old_state;


	std::vector<Evolution> evolutions = get_input<Evolution>("day12.txt");

	std::unordered_map<std::string, char> evolution_map;

	for(auto ev : evolutions){
		evolution_map[ev.prior_states] = ev.new_state;
	}


	std::cout << "                                            0         1         2         3\n";
	std::cout << "                                            0         0         0         0\n";
	std::cout << " 0: " << old_state << "\n";

	for(int i = 0; i < 20; i ++){
		new_state = UpdateState(old_state, evolution_map);
		if(i < 9) std::cout << " ";
		std::cout << i +1 << ": " << new_state << "\n";
		old_state = new_state;
	}


	int sum = 0;
	for( int i = 0 ; i < new_state.size(); i++){
		if(new_state[i] == '#'){
			// std::cout << (i-40) << ", ";
			sum += (i-40);
		}
	}
	std::cout << "Part 1 : " << sum << "\n";




	// Part 2

	// Will need a smarter way of dealing with edge cases (or a really dumb one)
	// "....." -> ., so buffer each end with ".....". If the the newstate does not begin/end
	// with ".....", add points to either end until they do. Might be easier to just add 5 points
	// at a time rather than count out the points necessary




	int64_t edge_buffer_n = 10;
	std::string edge_buffer(edge_buffer_n,'.');
	


	old_state = "###..###....####.###...#..#...##...#..#....#.##.##.#..#.#..##.#####..######....#....##..#...#...#.#";
	// std::cout << edge_buffer << "\n";
	old_state = edge_buffer + old_state + edge_buffer;
	// new_state.clear();
	// new_state.reserve(10000);
	new_state = old_state;

	int pots_added_left = 0;

	for(int64_t i = 0; i < 5000; i ++){
		new_state = UpdateState(old_state, evolution_map);


		// std::cout << "size : " << new_state.length() << "\n";

		if(new_state.substr(0,5) != "....."){
			// std::cout << "Need to expand left!\n";
			new_state = "....." + new_state;

			pots_added_left += 5;
		}

		if(new_state.substr(new_state.length()-5,5) != "....."){
			
			new_state = new_state + ".....";
			// new_state.resize(new_state.length() + 5,'.');
			// std::cout << "Need to expand right!\n";
		}

		// std::cout << i +1 << ": " << new_state << "\n";

		old_state = new_state;

	}




	sum = 0;
	for( int i = 0 ; i < new_state.size(); i++){
		if(new_state[i] == '#'){
			// std::cout << (i-edge_buffer_n - pots_added_left) << ", ";
			sum += (i-edge_buffer_n - pots_added_left);
		}
	}
	std::cout << "\n";
	std::cout << "Part 2 : " << sum << "\n";



// std::cout << new_state << "\n";
// std::cout << new_state.substr(0,5) << "\n";
// std::cout << new_state.substr(new_state.size()-5,5) << "\n";


	return 0;
}

