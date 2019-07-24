
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

// A utility function to find next to top in a stack 
Point nextToTop(std::stack<Point> &S) 
{ 
    Point p = S.top(); 
    S.pop(); 
    Point res = S.top(); 
    S.push(p); 
    return res; 
} 



int main(){

	std::vector<Point> points = get_input<Point>("day06-test.txt");



	// Find bottom left most point (maximum y, then minimum x)
	Point p0 = {1000,-1000};
	for(auto p : points){
		if(p.y > p0.y) p0 = p;
		else if(p.y == p0.y) if(p.x < p0.x) p0 = p;
	}

	std::cout << "Min : " << p0 << "\n";

	// Sort points by polar angle
	std::sort(points.begin(), points.end(), [p0](Point a, Point b){
		return orientation(p0,a,b) >= 0;
	});


	//

	std::stack<Point> convex_hull;
	convex_hull.push(points[0]);
	convex_hull.push(points[1]);
	convex_hull.push(points[2]);

	for(int i = 3; i < points.size(); i++){
		while(orientation(nextToTop(convex_hull), convex_hull.top(), points[i]) != 1)
			convex_hull.pop();
		convex_hull.push(points[i]);
	}

	while (!convex_hull.empty()) 
   { 
       Point p = convex_hull.top(); 
       std::cout << "(" << p.x << ", " << p.y <<")" << std::endl; 
       convex_hull.pop(); 
   } 
	std::cout << "\n";

	std::vector<Point> S;
	S.push_back(points[0]);
	S.push_back(points[1]);
	S.push_back(points[2]);

	for(int i = 3; i < points.size(); i++){
		while(orientation(S[S.size()-2], S[S.size()-1], points[i]) != 1)
			S.pop_back();
		S.push_back(points[i]);
	}

	for(auto p : S){
		std::cout << p << "\n";
	}




	return 0;
}
