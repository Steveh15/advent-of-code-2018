
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
#include <numeric>

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


private:
		int id;

	public: 

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


    std::unordered_map<int, int> gsm;
    std::unordered_map<int, SleepArray> gsm2;




    int current_guard_id;
    double sleep_min = 0;
    double sleep_wake = 0;

	for(auto l : logs){
		std::regex_search(l.message, matches, id_pat);
		// std::cout << l << "\n";
		if(!matches.empty()){
			current_guard_id = std::stoi(matches[1]);
			// std::cout << "Current guard : " << current_guard_id << "\n";
			// guards.insert(std::make_pair(current_guard_id,Guard(current_guard_id)));
		}
		if(l.message == " falls asleep"){
			// std::cout << getDateString(l) << "\n";
			// std::cout << "Asleep at : " << l.minute << "\n";
			sleep_min = l.minute;
		}
		if(l.message == " wakes up"){
			// std::cout << getDateString(l) << "\n";
			// std::cout << "Wake up at : " << l.minute << "\n";
			gsm[current_guard_id] +=l.minute - sleep_min;

			for(int i = sleep_min; i < l.minute; i++){
				gsm2[current_guard_id].arr[i] += 1;
			}	
		}

	}

	for(auto & m : gsm2){
		std::cout << m.first << "\n";
		for(auto min : m.second.arr){
			std::cout << min << " ";
		}
		std::cout << "\ntotal << " << std::accumulate(m.second.arr.begin(), m.second.arr.end(),0) << "\n";
		std::cout << "\n\n";
	}

	auto it = std::max_element(gsm2.begin(),gsm2.end(), [](std::pair<int,SleepArray> a, std::pair<int,SleepArray> b){
		return std::accumulate(a.second.arr.begin(), a.second.arr.end(),0) < std::accumulate(b.second.arr.begin(), b.second.arr.end(),0);
	});

	std::cout << it->first << "\n";

	auto it2 = std::max_element(it->second.arr.begin(), it->second.arr.end());
	std::cout << it2 - it->second.arr.begin() << "\n";

	std::cout << "Part one answer : " << it->first*(it2 - it->second.arr.begin()) << "\n";


	/*
		Answer is 77084,
			2753*28
	
		2753
0 1 1 2 4 6 6 6 7 7 7 8 8 9 10 10 10 11 11 11 12 12 12 12 12 12 13 14 14 14 13 13 12 12 11 11 11 11 12 11 11 11 10 10 10 10 9 9 9 9 9 9 6 5 5 3 3 3 2 1 
total << 523

		Get most slept guard
			Use max_element
		Get most inute for that guard
			Use max_element?
			it - vec.begin()
	*/


	// std::cout << gsm2[12].arr[2] << "\n";

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

		4) Friend functions allow you to give specific classes/functions access to private methods and data (rather than having
			to give all functions/classes access by setting it public). The case above we have used an operator which takes
			a guard as an argument but still has access to that gaurds private data.

			In general terms, this means we can write functions in the form f(x) instead of x.f() where it is convenient. In our case
			we have essentially used f(x,y) instead of x.f(y).
	
*/
