
#include <iostream>
#include <algorithm>
#include <map>
#include <stack>

#include "include/get_input.hpp"



struct Point{
	int x;
	int y;
};

std::istream& operator>>(std::istream& is, Point& coord)
{
	char c;
	int x,y;
	is >> x >> c >> y;
	coord = Point{x,y};
	return is;
}

std::ostream& operator<<(std::ostream& out, const Point& coord)
{
	out << "[" << coord.x << ", " << coord.y << "]";
	return out;
}

bool operator==(const Point & lhs, const Point & rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(const Point & lhs, const Point & rhs)
{

	if(lhs.x == rhs.x) return lhs.y < rhs.y;
	else return lhs.x < rhs.x;
}


int distance(const Point & x1, const Point & x2){
	return abs(x2.x - x1.x) + abs(x2.y-x1.y);
}


double orientation(const Point & p0, const Point & p1, const Point & p2){
	// Cross product of the vectors from p0 to p1/p2.
	// If positive, then counter clockwise turn
	// If negative, then clockwise turn
	int val = (p1.x - p0.x) * (p2.y - p0.y) - 
              (p2.x - p0.x) * (p1.y - p0.y); 
    if (val == 0) return 0;
    return (val > 0) ? -1: 1;

	// -1 : clockwise
    //	0 : in a line
    //  1 : counter clockwise
}

std::vector<Point> closestPoints(const Point & coord, const std::vector<Point> & coord_list){
    // Brute force this for now, could return later to make it log N
	int min_distance = 10000;
	std::vector<Point> closest_points;
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


bool point_in(const Point & p, const std::vector<Point> ps){

		for(auto c : ps){
			if(p == c){
				return true;
			}
		}
		return false;
}



int main(){

	std::vector<Point> points = get_input<Point>("day06.txt");



	// 1)  Define grid area to search over (Can't think of an easy way to do this which isn't more effort than it's worth, so just make it suitably big. 
    //      it probably won't be bigger than the bounding box but that isn't guarenteed)
	// 2)  Loop over each cell in area
	// 	       For each cell find closest point and create a map entry for it (if there are two or more, don't)
    // 3) Find which cell is referenced the most times
    // 4) Done!



	std::map<Point, Point> grid_closest_points;

	std::vector<Point> closest_points;
	Point ref;

	int grid_size = 500;

    for(int i = 0; i < grid_size; i ++){
        for(int j = 0; j < grid_size; j++){
            ref = {i,j};
            closest_points = closestPoints(ref, points);
            if(closest_points.size()  == 1){
                grid_closest_points[ref] = closest_points[0];
            }
        }
    }



    std::map<Point, int> sum_map;

  	for(std::map<Point, Point>::const_iterator it1 = grid_closest_points.begin(); it1 != grid_closest_points.end(); ++it1){
        sum_map[it1->second] += 1;
    }

    // Find convex hull (Graham scan)
    	Point p0 = {1000,-1000};
	for(auto p : points){
		if(p.y > p0.y) p0 = p;
		else if(p.y == p0.y) if(p.x < p0.x) p0 = p;
	}

	std::sort(points.begin(), points.end(), [p0](Point a, Point b){
		return orientation(p0,a,b) >= 0;
	});


	std::vector<Point> S;
	S.push_back(points[0]);
	S.push_back(points[1]);
	S.push_back(points[2]);

	for(int i = 3; i < points.size(); i++){
		while(orientation(S[S.size()-2], S[S.size()-1], points[i]) != 1)
			S.pop_back();
		S.push_back(points[i]);
	}

	// for(auto p : S){
	// 	std::cout << p << "\n";
	// }

	// Remove points on hull



   for(auto c : sum_map){
        std::cout << c.first << ", " << c.second << "\n";
    }
    std::cout << "\n";
	for(std::map<Point, int>::iterator it = sum_map.begin(); it != sum_map.end();){
		if(point_in(it->first, S)){
			sum_map.erase(it++);
		}else {
			++it;
		}
	}


   for(auto c : sum_map){
        std::cout << c.first << ", " << c.second << "\n";
    }



    // Part 2


    // std::map<Point, int> min_distance_sum_map;
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
