#include <iostream>
#include <fstream>
#include <map>

int main(){

	std::ifstream inFile;

	inFile.open("input1.txt");
	if (!inFile) {
 	   std::cerr << "Unable to open file datafile.txt";
 	   std::exit(1);   // call system to stop
	}

	int x = 0;
	int sum = 0;

	while (inFile >> x) {
		sum = sum + x;
		
	}

	std::cout << "Answer 1 : "  << sum << "\n";






	return 0;
}
