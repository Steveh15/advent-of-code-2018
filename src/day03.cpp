



#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "include/get_input.hpp"
// https://github.com/Bogdanp/awesome-advent-of-code#c-2
// https://github.com/Chrinkus/advent-of-code-2018
// https://github.com/LukeMoll/adventofcode2018/blob/master/src/day03.cpp

using namespace std;


struct Claim{
	string s1 = "null";
	string s2 = "null";
};

istream& operator>>(std::istream& is, Claim& claim)
{
    char c;
    int id, x, y, w, h;
    string str1, str2;
    //    #          @         ,         :         x
    is >> str1 >> str2;
    claim = Claim{ str1, str2 };

    return is;
}

ostream& operator<<(std::ostream& out, const Claim& claim)
{
	out << claim.s1 + ", " +  claim.s2;
	return out;
}


int main(){

	// get_lines<string>("test.txt");

	string file = "day03.txt";

	ifstream is ("../inputs/" + file );

		if(!is.is_open()) {
	        throw runtime_error("Could not open puzzle input file");
	    }

	vector<Claim> v;

	Claim s;

	while(is >> s){
		v.push_back(s);
		// cout << s << "\n ";
	}

	for(auto s : v) cout << s << "\n";


	Claim c1 = {"ashdj", "hasjdh"};
	cout << c1 << "\n";



}