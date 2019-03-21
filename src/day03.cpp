#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>

#include "include/get_input.hpp"



constexpr int fabric_size = 1000;

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
    //    #          @         ,         :         x
   	is >> c >> id >> c >> x >> c >> y >> c >> w >> c >> h;
    claim = Claim{id,x,y,w,h };
    return is;
}

std::ostream& operator<<(std::ostream& out, const Claim& claim)
{
	out << "[" << claim.id << ", (" << claim.x << "," << claim.y << "), " << claim.width << "x" << claim.height  << "]";
	return out;
}


bool operator!=(const Claim& lhs, const Claim& rhs)
{
	return lhs.id != rhs.id;
}



bool ClaimsOverlap(const Claim & c1, const Claim & c2){

	int top_edge_1 = c1.y;
	int bottom_edge_1 = c1.y + c1.height - 1;

	int top_edge_2 = c2.y;
	int bottom_edge_2 = c2.y + c2.height - 1;

	int left_edge_1 = c1.x;
	int right_edge_1 = c1.x + c1.width - 1;

	int left_edge_2 = c2.x;
	int right_edge_2 = c2.x + c2.width - 1;
	
	//   1 below 2				   or  2 below 1				 or  1 to right of 2		   or  2 to left of 1
	if( top_edge_1 > bottom_edge_2 || bottom_edge_1 < top_edge_2 || left_edge_1 > right_edge_2 || right_edge_1 < left_edge_2){
		return false;
	}
	else return true;

}


void MarkOverlapArea( const Claim & c1, const Claim & c2, std::vector<std::vector<int>> & fabric){

	int overlap_x = std::max(c1.x, c2.x);
	int overlap_y = std::max(c1.y, c2.y);
	int overlap_width = std::min(c1.x + c1.width, c2.x + c2.width) - overlap_x;
	int overlap_height = std::min(c1.y + c1.height, c2.y + c2.height) - overlap_y;

	for(int i = overlap_x; i < overlap_x + overlap_width; i++){
		for(int j = overlap_y; j < overlap_y + overlap_height; j++){
			if(fabric[i][j] == 0) fabric[i][j] = 1;
		}
	}

}


int PartOne(const std::vector<Claim> & claims){

	// Create fabric
	std::vector<std::vector<int>> fabric(fabric_size);
	std::vector<int> row(fabric_size);
	std::fill(row.begin(), row.end(),0);
	std::fill(fabric.begin(), fabric.end(),row);

	for(int i = 0; i < claims.size(); i++){
		for(int j = i + 1; j < claims.size(); j++){

			if(ClaimsOverlap(claims[i], claims[j]))
				MarkOverlapArea(claims[i], claims[j], fabric);
		}	
	}

	int p1_solution = std::accumulate(fabric.begin(), fabric.end(),0, 
		[](int current, std::vector<int> row){ 
			return current + std::accumulate(row.begin(),row.end(),0);
		}
	);

	return p1_solution;
}


int PartTwo(const std::vector<Claim> & claims){
	bool overlaps = false;
	for(auto c1 : claims){

		overlaps = false;

		for(auto c2 : claims)
			if(c1 != c2 && ClaimsOverlap(c1,c2))
				overlaps = true;

		if(!overlaps)
			return c1.id;

	}
	return -1;
}


int main(){

	std::vector<Claim> claims = get_lines<Claim>("day03.txt");


	std::cout << "Part 1 solution : " << PartOne(claims) << "\n";
	std::cout << "Part 2 solution : " << PartTwo(claims) << "\n";


	return 0;
}

/*

	Things learned
		1) Can overwrite >> and << operators pretty easily to make in/outputing data very easy.	
		2) Trick to get index when using a range-for loop, int index = &element - &container[0];
		3) Cannot declare large stuff (like an array with a million ints) on the stack, need to do it on
			the heap. Using normal pointers here, will try using smart pointers / containers on future
			days.
		4) const and constexpr are different
		5) Lambdas are powerful

*/