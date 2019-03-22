
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <regex>

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


class Guard{

	public: 
		int id;


		Guard(int id_) : id(id_){

	}


	bool operator==(const Guard & rhs) const {
		return id == rhs.id;
	}

	bool operator<(const Guard & rhs) const {
		return id < rhs.id;
	}

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


// This would be unecessary if I just read the logs in as strings,
// but this is a useful exercise in getting familiar with std::sort
bool operator<(const Log & a, const Log & b){
	if(a.year < b.year)
		return true;
	else if(a.year > b.year)
		return false;
	else{
		if(a.month < b.month)
			return true;
		else if(a.month > b.month)
			return false;
		else {
			if(a.day < b.day)
				return true;
			else if(a.day > b.day)
				return false;
			else {
				if(a.hour < b.hour)
					return true;
				else if(a.hour > b.hour)
					return false;
				else {
					if(a.minute < b.minute)
						return true;
					else if(a.minute > b.minute)
						return false;
					else 
						return true;
				}
			}
		}
	} 
}



int main(){

	std::vector<Log> logs = get_lines<Log>("day04.txt");

	std::sort(logs.begin(), logs.end());

	static const std::regex id_pat {R"(Guard\s#(\d+))"};
    std::smatch matches;
    std::set<Guard> guards;

    int current_guard;

	for(auto l : logs){
		std::regex_search(l.message, matches, id_pat);
		std::cout << l << "\n";
		if(!matches.empty()){
			// std::cout << matches[1] << "\n";
			current_guard = std::stoi(matches[1]);
			guards.insert(Guard(current_guard));
		}

	}


	std::cout << guards.size() << "\n";



/*
	1) Search for all terms that contains "Guard #xxxx", create a guar

*/
 //    static const std::regex ts_pat {R"(:(\d{2}))"};
	// auto test = logs[0].message;


	// for(auto t : matches){
	// 	std::cout << t << "\n";
	// }

	// std::cout << test << "\n";




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