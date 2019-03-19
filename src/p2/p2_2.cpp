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

	int term = 0;
	while (inFile >> x) {
		input.push_back(x);
		term += 1;
	}

	int diffs = 0;
	int found_solution = false;
	int last_diff_position = 0;
	std::string matching_id_one  = "";
	int length = input.size();

	for(int i = 0; i < length; i++)
	{
		for(int j = i + 1; j < length; j++){
			diffs = 0;

			for(int k = 0 ; k < input[i].size(); k++){
				if(input[i][k] !=  input[j][k]) {
					diffs += 1;
					last_diff_position = k;
				}
			}
			if(diffs == 1){
				std::cout << "Found it!\n";
				std::cout << "Comparing " << i << " against " << j << "\n";
				std::cout << input[i] << ", " << input[j] << "\n";
				std::cout << "Difference at position " << last_diff_position << "\n";
				matching_id_one = input[i];
				found_solution = true;
			}
			if(found_solution) break;
		}
		if(found_solution) break;
	}

	std::string::iterator it = matching_id_one.begin();
	std::advance(it,last_diff_position);

	matching_id_one.erase(it);
	std::cout << "Solution : " <<  matching_id_one << "\n";


	return 0;
}
