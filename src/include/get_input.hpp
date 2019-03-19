#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>



template<typename T>
std::vector<T> get_lines(std::string file){

	std::ifstream is ("../inputs/" + file );

		if(!is.is_open()) {
	        throw std::runtime_error("Could not open puzzle input file");
	    }

	    std::vector<T> v;
	    T t;
    	while(is >> t){
			v.push_back(t);
		}
	    return v;

};
