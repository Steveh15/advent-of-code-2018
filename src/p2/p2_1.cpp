#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

int main(){

	std::ifstream inFile;

	inFile.open("input.txt");
	if (!inFile) {
 	   std::cerr << "Unable to open file datafile.txt";
 	   std::exit(1);   // call system to stop
	}

	std::string x = "";

	std::vector<std::string> input;

	while (inFile >> x) {
		input.push_back(x);
	}

	std::map<char,int> char_map;
	std::map<char,int>::iterator it;

	int three_count = 0;
	int two_count = 0;
	bool two_already_counted = false;
	bool three_already_counted = false;

	for(auto x : input){

		for(char c : x){
			char_map[c] += 1;
		}

		it = char_map.begin();
		two_already_counted = false;
		three_already_counted = false;

		for ( it = char_map.begin(); it != char_map.end(); it++ )
		{
			if(it->second == 2 && !two_already_counted) {
				two_count += 1;
				two_already_counted = true;
			}
			if(it->second == 3 && !three_already_counted) {
				three_count += 1;
				three_already_counted = true;
			}
		}
		char_map.clear();
	}


	std::cout << two_count*three_count << "\n";



	return 0;
}
