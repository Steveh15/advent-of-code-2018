#include <string>
#include <iostream>
#include <ctype.h>
#include <algorithm>
#include <vector>

#include "include/get_input.hpp"

using namespace std;

auto test(const string & str){
	return std::adjacent_find(str.begin(), str.end(), [](char a, char b){
		return (std::toupper(a) == std::toupper(b))  && (a != b);
	});
}

string remove_polarised_units(string str){
	auto it = test(str);
	while(it != str.end()){
		 str.erase(it, it + 2);
		 it = test(str);
	}
	return str;
}

int main(){

	std::string input(get_lines<std::string>("day05.txt")[0]);
	std::cout << "Part one solution : " << remove_polarised_units(input).size() << "\n";


	// std::vector<int> lengths;
	// string test_str;

	// for(char i = 'a'; i <= 'z'; i++){
	// 	test_str = input;
	// 	test_str.erase(std::remove_if(test_str.begin(), test_str.end(), [i](char a){
	// 		return tolower(a) == i || toupper(a) == toupper(i);
	// 	}),test_str.end());
	// 	lengths.push_back(remove_polarised_units(test_str).size());
	// }

	// std::cout << "Part two solution : " << *std::min_element(lengths.begin(),lengths.end()) << "\n";


	return 0;
}


