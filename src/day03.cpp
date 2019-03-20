#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include "include/get_input.hpp"
// https://github.com/Bogdanp/awesome-advent-of-code#c-2
// https://github.com/Chrinkus/advent-of-code-2018
// https://github.com/LukeMoll/adventofcode2018/blob/master/src/day03.cpp


struct Claim{
	int id;
	int x;
	int y;
	int width;
	int height;
};

std::istream& operator>>(std::istream& is, Claim& claim)
{
    char c;
    int id, x, y, w, h;
    std::string str1, str2;
    //    #          @         ,         :         x
   	is >> c >> id >> c >> x >> c >> y >> c >> w >> c >> h;
    claim = Claim{id,x,y,w,h };
    return is;
}

std::ostream& operator<<(std::ostream& out, const Claim& claim)
{
	out << claim.id << ", (" << claim.x << ", " << claim.y << "), " << claim.width << " x " << claim.height ;
	return out;
}


int main(){

	std::vector<Claim> input = get_lines<Claim>("day03.txt");

	std::vector<int> arr(1000);
	arr = {1};
	// std::vector<std::vector<int,1000>,1000> arr = {0};

	// int[] *arr = new int[1000][1000];

	// int* arr = new int[1000*1000];
	// *arr = {0};

	// for(auto x : arr){
	// 	for(auto y : x){
	// 			std::cout << y << ", ";
	// 	}		
	// 	std::cout << "\n";
	// }
	std::cout << arr[4,4];
}