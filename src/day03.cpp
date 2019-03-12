



#include <iostream>

#include "include/get_input.hpp"
// https://github.com/Bogdanp/awesome-advent-of-code#c-2
// https://github.com/Chrinkus/advent-of-code-2018
// https://github.com/LukeMoll/adventofcode2018/blob/master/src/day03.cpp


bool cond1(bool in){
	std::cout << "Doing cond 1\n";
	return in;
}

bool cond2(bool in){
	std::cout << "Doing cond 2\n";
	return in;
}

int main(){


	std::cout << "|| test\n";
	cond1(true) || cond2(true);
	std::cout << "\n";
	cond1(true) || cond2(false);
	std::cout << "\n";
	cond1(false) || cond2(true);
	std::cout << "\n";
	cond1(false) || cond2(false);

	std::cout << "\n";
	std::cout << "&& test\n";
	cond1(true) && cond2(true);
	std::cout << "\n";
	cond1(true) && cond2(false);
	std::cout << "\n";
	cond1(false) && cond2(true);
	std::cout << "\n";
	cond1(false) && cond2(false);

}