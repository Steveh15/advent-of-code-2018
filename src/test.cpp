


#include <string>
#include <iostream>



int main(){


	std::string str = "Hello";


	std::cout << str.size() << "\n";
	std::cout << str.length() << "\n";


	str = str + "Some stuff on the end";

	std::cout << str.size() << "\n";
	std::cout << str.length() << "\n";



	str = "Some stuff on the beginning" + str;

	std::cout << str.size() << "\n";
	std::cout << str.length() << "\n";

	return 0;
}