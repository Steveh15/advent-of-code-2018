
#include <iostream>
#include <vector>


class Vector2D
{
public:

	int x, y;

	Vector2D() : x(0), y(0){};

	Vector2D(const int & _x, const int & _y) : x(_x), y(_y){};

	~Vector2D();
	
};

class Cart
{

public:


	enum next_turn
	{
		left,
		ahead,
		right
	};

	enum direction
	{
		north,
		south,
		east,
		west
	};

	Cart();
	~Cart();



	
};


int main(){




}


