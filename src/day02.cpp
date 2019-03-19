



#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include "include/get_input.hpp"
// https://github.com/Bogdanp/awesome-advent-of-code#c-2
// https://github.com/Chrinkus/advent-of-code-2018
// https://github.com/LukeMoll/adventofcode2018/blob/master/src/day03.cpp



std::pair<bool, bool> check_id(std::string s){

	std::pair<bool,bool> bool_pair = std::make_pair(false,false);
	std::map<char,int> char_map;
	for(char c : s){
			char_map[c] += 1;
		}

	std::vector<int> counts;
	for ( std::map<char,int>::iterator it = char_map.begin(); it != char_map.end(); it++ ){
		counts.push_back(*it);
	}

	for ( std::map<char,int>::iterator it = char_map.begin(); it != char_map.end(); it++ )
		{
			if(!bool_pair.first && it->second == 2) {
				bool_pair.first = true;
			}
			if(!bool_pair.second && it->second == 3) {
				bool_pair.second = true;
			}
			if( bool_pair.first && bool_pair.second ) break; // Contains a 2 and 3, can stop searching

		}
		return bool_pair;
}



int PartOne(const std::vector<std::string> & input){

	std::map<char,int> char_map;
	std::pair<int,int> count_pair = std::make_pair(0,0);
	std::pair<bool,bool> count_pair_bool;

	for(auto x : input){


		// for(char c : x){
		// 	char_map[c] += 1;
		// }

		// count_pair_bool = std::make_pair(false,false);

		// for ( std::map<char,int>::iterator it = char_map.begin(); it != char_map.end(); it++ )
		// {
		// 	if(!count_pair_bool.first && it->second == 2) {
		// 		count_pair.first += 1;
		// 		count_pair_bool.first = true;
		// 	}
		// 	if(!count_pair_bool.second && it->second == 3) {
		// 		count_pair.second += 1;
		// 		count_pair_bool.second = true;
		// 	}
		// 	if( count_pair_bool.first && count_pair_bool.second ) break;

		// }

		// char_map.clear();
	}
	return count_pair.first*count_pair.second;
}


int PartTwo(const std::vector<std::string> & changes){
	return -1;
}


int main(){

	std::vector<std::string> input = get_lines<std::string>("day02.txt");


	std::cout << "Part 1 answer : " << PartOne(input) << "\n";
	// std::cout << "Part 2 answer : " << PartTwo(input) << "\n";



}