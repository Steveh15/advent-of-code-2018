
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
// #include <pair>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <map>

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

		std::map<std::string, int> sleep_minutes;
		std::map<std::string, int> wake_minutes;

		Guard(int id_) : id(id_){

		}

		bool operator==(const Guard & rhs) const {
			return id == rhs.id;
		}

		bool operator<(const Guard & rhs) const {
			return id < rhs.id;
		}

		void addWakeMinute( const std::string & date, const int & min){
			wake_minutes[date] = min;
		}

		void addSleepMinute( const std::string & date, const int & min){
			sleep_minutes[date] = min;
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
    // std::set<Guard> guards;
    std::unordered_map<int, Guard> guards;
    // std::map<int, Guard> guards;

    std::string 

    int current_guard_id;

	for(auto l : logs){
		std::regex_search(l.message, matches, id_pat);
		std::cout << l << "\n";
		if(!matches.empty()){
			// std::cout << matches[1] << "\n";
			// current_guard_id = std::stoi(matches[1]);
			// guards.insert(Guard(current_guard));
			// guards[current_guard_id] = Guard(current_guard_id);
			guards.insert(std::make_pair(std::stoi(matches[1]),Guard(current_guard_id)));
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
		1) Don't just default to vector, map or set when picking a container. There are subtle differences
			between the containers that might be more optimal for a given situation, so learn which is best when
			and pick appropriately (after all speed is the point of using C++)

			My basic understanding
			unordered_map:
				fast for lookup, not as good for everything else
				larger memory footprint
			map:
				good for iterating over, adding/removing elements
				slower lookup

*/