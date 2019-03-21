#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>

#include "include/get_input.hpp"
// https://github.com/Bogdanp/awesome-advent-of-code#c-2
// https://github.com/Chrinkus/advent-of-code-2018
// https://github.com/LukeMoll/adventofcode2018/blob/master/src/day03.cpp



struct Log{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	std::string message;
};

std::istream& operator>>(std::istream& is, Log& log)
{
    char c;
    int y,m,d,h,min;
    std::string msg;
   	is >> c >> y >> c >> m >> c >> d >> h >> c >> min >> c;
   	std::getline(is,msg);
    log = Log{y,m,d,h,min,msg};
    return is;
}

std::ostream& operator<<(std::ostream& out, const Log& log)
{
	out << "[" << log.year << "-" << log.month << "-" << log.day << " " << log.hour << ":" << log.minute << "] " << log.message;
	return out;
}

bool operator<(const Log & log1, const Log & l2){
	return true;
}

bool operator>(const Log & log1, const Log & l2){
	return true;
}

// bool operator!=(const Claim& lhs, const Claim& rhs)
// {
// 	return lhs.id != rhs.id;
// }



int main(){

	std::vector<Log> logs = get_lines<Log>("day04.txt");

	for(auto l : logs)
		std::cout << l << "\n";

	return 0;
}

/*

	Things learned
		1) Can overwrite >> and << operators pretty easily to make in/outputing data very easy.	
		2) Trick to get index when using a range-for loop, int index = &element - &container[0];
		3) Cannot declare large stuff (like an array with a million ints) on the stack, need to do it on
			the heap. Using normal pointers here, will try using smart pointers / containers on future
			days.
		4) const and constexpr are different
		5) Lambdas are powerful

*/