#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "include/get_input.hpp"


// Returns a pair of booleans that indicate if the string contains any letter exactly twice and exactly three times
std::pair<bool, bool> check_id(const std::string & s){

	std::pair<bool,bool> bool_pair = std::make_pair(false,false);
	std::map<char,int> char_map;

	for(const char c : s) 
		char_map[c] += 1;

	for ( std::map<char,int>::iterator it = char_map.begin(); it != char_map.end(); it++ )
		{
			if(!bool_pair.first && it->second == 2) 
				bool_pair.first = true;

			if(!bool_pair.second && it->second == 3)
				bool_pair.second = true;
			
			if( bool_pair.first && bool_pair.second )
				break; // Contains a 2 and 3, can stop searching

		}
		return bool_pair;
}



int PartOne(const std::vector<std::string> & input){

	std::map<char,int> char_map;
	std::pair<int,int> count_pair = std::make_pair(0,0);
	std::pair<bool,bool> count_pair_bool;

	for(auto x : input){

		count_pair_bool = check_id(x);
		if(count_pair_bool.first) count_pair.first += 1;
		if(count_pair_bool.second) count_pair.second += 1;

	}

	return count_pair.first*count_pair.second;
}


std::string PartTwo(const std::vector<std::string> & input){

	for(std::vector<std::string>::const_iterator it1 = input.begin(); it1 != input.end(); ++it1){
		for(std::vector<std::string>::const_iterator it2 = it1+1; it2 != input.end(); ++it2){
			
			std::string str1 = *it1;

			auto strit1  = std::mismatch(std::begin(str1),std::end(str1),std::begin(*it2));
			auto strit2 = std::mismatch(++strit1.first,std::end(str1),++strit1.second);

			// If there is one mismatch && there is not a second mismatch
			if(strit1.first != std::end(str1) && strit2.first == std::end(str1)){
				str1.erase(strit1.first);
				return str1;
			}

		}
	}

	return "No solution";

}


int main(){

	std::vector<std::string> input = get_lines<std::string>("day02.txt");

	std::cout << "Part 1 answer : " << PartOne(input) << "\n"; // Correct answer = 5928
	std::cout << "Part 2 answer : " << PartTwo(input) << "\n";


	return 0;
}


/*
	Things learnt
		1) Pairs are good, saves creating multilple count_two and count_three variables
		2) (Not used here) Can compare pointers when looping over an iterable to ensure 
			the same object is not checked twice
		3) std::mismatch
		4) (Not used here) There are better ways for looping over a vector with iterators, remember to use in
			future days.


*/