#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

#include "include/get_input.hpp"

class Vector2D{

public:
	int x, y;

	Vector2D(){
		x = 0;
		y = 0;
	}
	Vector2D(int _x, int _y) : x(_x), y(_y){}
};

class Point{

public:
	Vector2D x;
	Vector2D v;

	Point(){
		x = Vector2D();
		v = Vector2D();
	}

	void Update(){
		x.x += v.x;
		x.y += v.y;
	}

	Point(Vector2D _x, Vector2D _v) : x(_x) , v(_v){}
	friend std::ostream& operator<<(std::ostream& os, const Point& point);
};

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    os << "x : [" << point.x.x << ", " << point.x.y << "], v : [" << point.v.x << ", " << point.v.y << "]";
    return os;
}

std::istream& operator>>(std::istream& is, Point& point)
{
	char c;
	int x1, y1, x2, y2;
	std::string x,y;
	
	char carr[100];
	is.read(carr,10);
	is >> x1 >> c >> y1;
	is.read(carr,12);
	is >> x2 >> c >> y2;
	std::getline(is,x);
	
	Point np(Vector2D(x1,y1),Vector2D(x2,y2));

	point = np;
	return is;
}


int64_t boundingArea( const std::vector<Point> & points){

	int64_t min_y = 1000000;
	int64_t min_x = 1000000;

	int64_t max_x = -1000000;
	int64_t max_y = -1000000;

	for(auto p : points){
		if(p.x.x < min_x) min_x = p.x.x;
		if(p.x.y < min_y) min_y = p.x.y;

		if(p.x.x > max_x) max_x = p.x.x;
		if(p.x.y > max_y) max_y = p.x.y;
	}

	return (max_x-min_x)*(max_y-min_y);
}

void UpdatePoints(std::vector<Point> & points){
	for(auto & s : points){
		s.Update();
	}
}

void Draw(std::vector<Point> & points){

	int x_min = 1000000;
	int x_max = -1000000;
	int y_min = 1000000;
	int y_max = -1000000;

	for(auto p : points){
		if(p.x.x < x_min) x_min = p.x.x;
		if(p.x.y < y_min) y_min = p.x.y;
		if(p.x.x > x_max) x_max = p.x.x;
		if(p.x.y > y_max) y_max = p.x.y;
	}

	// This is an inefficient way of drawing but works for the current purpose
	for(int y = y_min; y <= y_max; y++){

		for(int x = x_min; x <= x_max; x++){

			bool here = false;
			for(auto s : points){
				if(s.x.x == x && s.x.y == y){
					here = true;
				}
			}
			if(here){
				std::cout << "#";
			}else
				std::cout << ".";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

int main(){


	std::vector<Point> points = get_input<Point>("day10.txt");


	int64_t min_bounding_area = 2000000000;
	int min_time_step = 0;

	for(int t = 1; t < 10100; t++){
		UpdatePoints(points);
		if(boundingArea(points) < min_bounding_area) {
			min_bounding_area = boundingArea(points);
			min_time_step = t;
		}


		if(t == 10054){
			 Draw(points);
		}
	}

	std::cout << "The min bounding area is " <<  min_bounding_area << "\n";

	std::cout << "This occurs at time step " <<  min_time_step << "\n";


	return 0;
}


/*
	Things I've learnt
		When ints start getting bit, stop using int and use something more appropriate. Also check that the calculations are doing what they should be
		doing because it's not always obvious when they're going wrong.

*/