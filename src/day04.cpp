
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <string>
#include <regex>

#include "include/get_input.hpp"


// Wrapper around an array to initate default values to 0;
class SleepArray{
public:
	std::array<int,60> arr;
	SleepArray(){
		arr = {0};
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

// Not used but useful for debugging
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
    std::unordered_map<int, SleepArray> gsm;


    int current_guard_id;
    double sleep_min = 0;

	for(auto l : logs){
		std::regex_search(l.message, matches, id_pat);
		if(!matches.empty()){
			current_guard_id = std::stoi(matches[1]);
		}
		if(l.message == " falls asleep"){
			sleep_min = l.minute;
		}
		if(l.message == " wakes up"){
			for(int i = sleep_min; i < l.minute; i++){
				gsm[current_guard_id].arr[i] += 1;
			}	
		}

	}


	// Part one

	// Find guard with most minutes asleep
	auto guard_it = std::max_element(gsm.begin(),gsm.end(), [](std::pair<int,SleepArray> a, std::pair<int,SleepArray> b){
		return std::accumulate(a.second.arr.begin(), a.second.arr.end(),0) < std::accumulate(b.second.arr.begin(), b.second.arr.end(),0);
	});
	// Find their most asleep minute
	auto min_it = std::max_element(guard_it->second.arr.begin(), guard_it->second.arr.end());

	std::cout << "Part one answer : " << guard_it->first*(min_it - guard_it->second.arr.begin()) << "\n";

	

	// Part two

	// Find guard who is most asleep at a specific minute
	guard_it = std::max_element(gsm.begin(),gsm.end(), [](std::pair<int,SleepArray> a, std::pair<int,SleepArray> b){
		return *std::max_element(a.second.arr.begin(), a.second.arr.end()) < *std::max_element(b.second.arr.begin(), b.second.arr.end());
	});
	// Find that minute
	min_it = std::max_element(guard_it->second.arr.begin(),guard_it->second.arr.end());

	std::cout << "Part two answer : " << guard_it->first*std::distance(guard_it->second.arr.begin(),min_it) << "\n";

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

			NOTE : didn't end up using it this code, so there are no friend functions here.

		5) Two different methods for finding index of iterator, see discussion here :
		 https://stackoverflow.com/questions/2152986/what-is-the-most-effective-way-to-get-the-index-of-an-iterator-of-an-stdvector
	
		6) min_it is an excellent pun and it's a shame no one will ever read this code in order to appreciate it.
*/
