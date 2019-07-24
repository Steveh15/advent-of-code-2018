
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

double polar_angle(const Point & x1, const Point & x2){

	return 0;
}





int main(){

	std::vector<Point> points = get_input<Point>("day06.txt");

	// for(auto p : points) {std::cout << p << "\n";}

	Point p0 = {1000,-1000};
	for(auto p : points){
		if(p.y > p0.y) p0 = p;
		else if(p.y == p0.y) if(p.x < p0.x) p0 = p;
	}

	std::cout << "Min : " << p0 << "\n";


	return 0;
}
