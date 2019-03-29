
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
// #include <pair>
#include <array>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <map>

#include "include/get_input.hpp"
// https://github.com/Bogdanp/awesome-advent-of-code#c-2
// https://github.com/Chrinkus/advent-of-code-2018
// https://github.com/LukeMoll/adventofcode2018/blob/master/src/day03.cpp



// Wrapper around an array to initate default values to 0;
class SleepArray{
public:
	std::array<int,60> arr;
	SleepArray(){
		arr = {0};
	}
};



class Guard {

	public: 
		int id;

		std::map<std::string, SleepArray> sleep_map;


		// Guard(){
		// 	id = 0;
		// }


		Guard(int id_) : id(id_){

		}

		bool operator==(const Guard & rhs) const {
			return id == rhs.id;
		}

		bool operator<(const Guard & rhs) const {
			return id < rhs.id;
		}

		// void addWakeMinute( const std::string & date, const int & min){
		// 	wake_minutes[date] = min;
		// }

		// void addSleepMinute( const std::string & date, const int & min){
		// 	sleep_minutes[date] = min;
		// }



		friend std::ostream &operator<<( std::ostream &output, const Guard &g) { 
			output << "F : " << g.id;
			return output;            
	    }
};




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

std::string getDateString(const Log & l){
	std::string date =  std::to_string(l.year) + std::string("-") + std::to_string(l.month) + std::string("-") +  std::to_string(l.day);
	return date;
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
    std::unordered_map<int, Guard> guards;


    int current_guard_id;

	for(auto l : logs){
		std::regex_search(l.message, matches, id_pat);
		// std::cout << l << "\n";
		if(!matches.empty()){
			current_guard_id = std::stoi(matches[1]);
			guards.insert(std::make_pair(current_guard_id,Guard(current_guard_id)));
		}
		if(l.message == " wakes up"){
			std::cout << getDateString(l) << "\n";
		}
	}



	// SleepMap s;
	// auto b = s.blah;
	// std::cout << s.blah << "\n";

	// for(auto i : s.sm){
	// 	std::cout << i << "\n";
	// }


    // Guard g = Guard(1);
    // std::cout << g << "\n";


    // std::map<int,Guard> newmap;

    // newmap.insert(std::make_pair(15,Guard(23)));

    // auto it = newmap.find(15);

    // auto blah = newmap[15];
    // std::cout << blah << "\n";
    // std::cout << it->second << "\n";

	// std::cout << guards.size() << "\n";



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

		2) using [] on a map requires that the object being accessed has a default constructor. If you don't want
			a default constructor, using find.

		3) Use std::to_string and std::string() when concatenating strings, then can do it with + operator as normal

*/