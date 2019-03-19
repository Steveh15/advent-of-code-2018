#include <iostream>
#include <fstream>
#include <map>
#include <vector>
int main(){

	std::ifstream inFile;

	inFile.open("input1.txt");
	if (!inFile) {
 	   std::cerr << "Unable to open file datafile.txt";
 	   std::exit(1);   // call system to stop
	}



	std::vector<int> changes;
	int x;
	while (inFile >> x) {
		changes.push_back(x);
	}

	std::vector<int>::iterator it = changes.begin();
	std::map<int,int> freqs;
	bool found_solution = false;
	int sum  = 0 ;
	int solution;

	int loops = 0;
	int term = 0;


	while(found_solution == false){

		sum += *it;
		freqs[sum] += 1;
		// std::cout << "Change : " << *it << ", " << "Sum : " << sum << ", Count = " << freqs[sum] << "\n";
		it++;


		if(freqs[sum] == 2){
			solution = sum;
			found_solution = true;
		}
		if(it == changes.end()){
			it = changes.begin();
		}

		term += 1;
		if(term > 100000000){
			//Terminate if stuck in infinite loop
			found_solution = true;
		}
	}

	std::cout << "Solution : " << solution << "\n";


	return 0;
}
