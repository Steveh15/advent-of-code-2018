
#include <iostream>
#include <algorithm>
#include <map>
#include <stack>

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

bool operator==(const Coord & lhs, const Coord & rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(const Coord & lhs, const Coord & rhs)
{

	if(lhs.x == rhs.x) return lhs.y < rhs.y;
	else return lhs.x < rhs.x;
}




int distance(const Coord & x1, const Coord & x2){
	return abs(x2.x - x1.x) + abs(x2.y-x1.y);
}


std::vector<Coord> closestPoints(const Coord & coord, const std::vector<Coord> & coord_list){
    // Brute force this for now, could return later to make it log N
	int min_distance = 10000;
	std::vector<Coord> closest_points;
	int dis;
	for(auto c : coord_list){

		dis = distance(c,coord);
		if(dis < min_distance){
			min_distance = dis;
			closest_points.clear();
			closest_points.push_back(c);
		}
		else if(dis == min_distance){
			closest_points.push_back(c);
		}
	}

	return closest_points;
}






int main(){

	std::vector<Coord> coords = get_input<Coord>("day06.txt");

	// for(auto c : coords){
	// 	std::cout << c << "\n";
	// }


	// To find which points have infinite area I think we'd need to calcualte the which
	// is a bit labourious, so instead we'll just search over a big enough grid and discard the 
	// min/max points on the x/y axis. Hopefully that will work

	// int min_x = std::min_element(coords.begin(),coords.end(), [](Coord a, Coord b){return a.x < b.x;})->x;
	// int max_x = std::max_element(coords.begin(),coords.end(), [](Coord a, Coord b){return a.x < b.x;})->x;
	// int min_y = std::min_element(coords.begin(),coords.end(), [](Coord a, Coord b){return a.y < b.y;})->y;
	// int max_y = std::max_element(coords.begin(),coords.end(), [](Coord a, Coord b){return a.y < b.y;})->y;


	// std:: cout << min_x << ", " << max_x << ", " << min_y << ", " << max_y << "\n";




	// 1)  Define grid area to search over (Can't think of an easy way to do this which isn't more effort than it's worth, so just make it suitably big. 
    //      it probably won't be bigger than the bounding box but that isn't guarenteed)
	// 2)  Loop over each cell in area
	// 	       For each cell find closest point and create a map entry for it (if there are two or more, don't)
    // 3) Find which cell is referenced the most times
    // 4) Done!



	std::map<Coord, Coord> grid_closest_points;

	std::vector<Coord> closest_points;
	Coord ref;

	int grid_size = 500;

  //   for(int i = 0; i < grid_size; i ++){
  //       for(int j = 0; j < grid_size; j++){
  //           ref = {i,j};
  //           closest_points = closestPoints(ref, coords);
  //           if(closest_points.size()  == 1){
  //               grid_closest_points[ref] = closest_points[0];
  //           }
  //           std::cout << "\n";
  //       }
  //   }

  //   std::map<Coord, int> sum_map;

  // for(std::map<Coord, Coord>::const_iterator it1 = grid_closest_points.begin(); it1 != grid_closest_points.end(); ++it1){
  //       sum_map[it1->second] += 1;
  //   }

    // std::cout << "\n";
    // for(auto c : sum_map){
    //     std::cout << c.first << ", " << c.second << "\n";
    // }

    // Graham scan
	std::stack<Coord> stack;
	int min_x = 1000;
	int min_y = 1000;
	Coord min_point;
	for(auto p : coords){
		if(p.x < min_x){
			min_x = p.x;
			min_y = p.y;
			min_point = {p.x,p.y};
		}
		else if(p.x == p.y){
			if(p.x < min_x){
				min_y = p.y;
				min_point = {p.x,p.y};
			}
		} 

	}

	std::cout << min_point << "\n";




    // Part 2


    // std::map<Coord, int> min_distance_sum_map;
    // int sum_distance;

    // grid_size = 500;
    // int sum = 0;

    //    for(int i = 0; i < grid_size; i ++){
    //     for(int j = 0; j < grid_size; j++){
    //         ref = {i,j};

    //         sum_distance = 0;
    //         for(auto c : coords){
    //             sum_distance += distance(ref,c);
    //         }
    //         if(sum_distance < 10000){
    //             ++sum;
    //         }
    //     }
    // }


    // std::cout << "answer : " << sum << "\n";

	return 0;
}
