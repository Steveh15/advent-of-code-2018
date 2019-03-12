#include <vector>
#include <string>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <exception>


using namespace std;

namespace AOC {

	ifstream getInputStream(std::string file) {
		ifstream is ("../inputs/" + file );

		if(!is.is_open()) {
	        throw runtime_error("Could not open puzzle input file");
	    }

		return is;
	}	

	vector<string> getLines(std::string day) {
		vector<string> lines = {};
		ifstream puzzleInput = getInputStream(day);
		string line;
	    while(getline(puzzleInput, line)) {
	        lines.push_back(line);
	    }
	    return lines;
	}
		
}
