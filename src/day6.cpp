
#include <iostream>
#include <algorithm>

#include "include/get_input.hpp"



struct Coord{
	int x;
	int y;
};

std::istream& operator>>(std::istream& is, Coord& coord)
{
    char c;
    int x,y;
   	is >> x >> c >> y;
    coord = Coord{x,y};
    return is;
}

std::ostream& operator<<(std::ostream& out, const Coord& coord)
{
	out << "[" << coord.x << ", " << coord.y << "]";
	return out;
}



int main(){

	std::vector<Coord> coords = get_input<Coord>("day06-test.txt");

	for(auto c : coords){
		std::cout << c << "\n";
	}


	// I think we can ignore all points on the bounding rectangle and just consider points inside it, 
	// so first thing to do is to get only those points

	int min_x = std::min_element(coords.begin(),coords.end(), [](Coord a, Coord b){
  		return a.x < b.x;
   	})->x;
	int max_x = std::max_element(coords.begin(),coords.end(), [](Coord a, Coord b){
  		return a.x < b.x;
   	})->x;
	int min_y = std::min_element(coords.begin(),coords.end(), [](Coord a, Coord b){
  		return a.y < b.y;
   	})->y;
	int max_y = std::max_element(coords.begin(),coords.end(), [](Coord a, Coord b){
  		return a.y < b.y;
   	})->y;


	std::vector<Coord> reduced_coords = coords;

	reduced_coords.erase(std::remove_if(reduced_coords.begin(), reduced_coords.end(), [min_x, max_x, min_y, max_y](Coord c){
			return c.x == min_x || c.x == max_x || c.y == min_y || c.y == max_y;
			return true;
		}),reduced_coords.end());

	std::cout << "Min x : " << min_x << "\n" ;
	std::cout << "Max x : " << max_x << "\n" ;
	std::cout << "Min y : " << min_y << "\n" ;
	std::cout << "Max y : " << max_y << "\n" ;


	for(auto c : reduced_coords){
		std::cout << c << "\n";
	}



	return 0;
}
