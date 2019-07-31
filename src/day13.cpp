
#include <iostream>
#include <vector>
#include <string>

#include "include/get_input.hpp"

class Vector2D
{
public:
	int x, y;
	Vector2D() : x(0), y(0){};
	Vector2D(const int & _x, const int & _y) : x(_x), y(_y){};
	friend bool operator==(const Vector2D& lhs, const Vector2D& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector);
};

bool operator==(const Vector2D& lhs, const Vector2D& rhs)
{
   	return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vector)
{
    os << "(" << vector.x << ", " << vector.y << ")";
    return os;
}

class Cart
{

public:

	enum class Turn
	{
		left=-1,
		ahead=0,
		right=1
	};

	enum class Direction
	{
		up = 0,
		right,
		down,
		left
	};

	Vector2D location;
	Direction direction;
	Turn next_turn;


	Cart();
	Cart(const Vector2D & _location, const int & _direction) : location(_location){
		direction = (Direction)_direction;
		next_turn = Turn::ahead;
	}
	friend std::ostream& operator<<(std::ostream& os, const Cart& cart);
};
std::ostream& operator<<(std::ostream& os, const Cart& cart)
{
    os << "Position : " << cart.location << ", Direction : " << (int)cart.direction << ", Next turn : " << (int)cart.next_turn;
    return os;
}


std::vector<Cart>::const_iterator find_collision(const std::vector<Cart> & cart_list){
	bool collision_found = false;
	std::vector<Cart>::const_iterator it = cart_list.end();
	for(int i = 0; i < cart_list.size(); i++){
		for(int j = i+1; j < cart_list.size(); j++){
			if(cart_list[i].location == cart_list[j].location){
				collision_found = true;
				it = cart_list.begin();
				std::advance(it,i);
			}
			if (collision_found) break;
		}
		if (collision_found) break;
	}
	return it;
}


void AdvanceTimeStep(const std::vector<std::string> & track, std::vector<Cart> & cart_list){
	for(auto & c : cart_list){
		if(c.direction == Cart::Direction::right){
			c.location.x += 1;
		}
		else if (c.direction == Cart::Direction::left){
			c.location.x -= 1;
		}
		else if (c.direction == Cart::Direction::up){
			c.location.y -= 1;
		}
		else if (c.direction == Cart::Direction::down){
			c.location.y += 1;
		}

		// if(track[c.location.y][c.location.x] == '+'){
		// 	std::cout << "At a cross road!\n";
		// }
		// if(track[c.location.y][c.location.x] == '\\'){
		// 	std::cout << "At a westward bend!\n";
		// 	if(c.direction == Cart::Direction::right){
		// 		// std::cout << "Is this triggering?\n";
		// 		// c.direction = Cart::Direction::down;
		// 	}
		// }
		// if(track[c.location.y][c.location.x] == '/'){
		// 	std::cout << "At a eastward bend!\n";
		// }
	}
}

void DrawTrack(std::vector<std::string> track, const std::vector<Cart> & cart_list){
		
	// std::cout << c.location.y << ", " << c.location.x << "\n";
	for(const auto & c : cart_list){
		std::cout << c.location.y << ", " << c.location.x << "\n";
		track[c.location.y][c.location.x] = '@';
		
	}

	for(const auto & t : track){
		std::cout << t << "\n";
	}

}



int main(){


	std::vector<std::string> track = get_lines<std::string>("day13-test.txt");
	
	int track_height, track_width;

	track_height  = track.size() ;
	track_width  = track[0].length() ;

	std::cout << "Track is " << track_width << " by " << track_height << "\n";


	std::vector<Cart> cart_list;
	// Mercifully it appears no tracks start on a cross road.
	for(int x = 0; x < track_width; x++){
		for(int y = 0; y < track_height; y++){
			if(track[y][x] == '^'){
				track[y][x] = '|';
				cart_list.push_back(Cart(Vector2D(x, y),0));
			}
			else if(track[y][x] == 'v'){
				track[y][x] = '|';
				cart_list.push_back(Cart(Vector2D(x, y),2));
				
			}
			else if(track[y][x] == '<'){
				track[y][x] = '-';
				cart_list.push_back(Cart(Vector2D(x, y),3));
			}
			else if(track[y][x] == '>'){
				track[y][x] = '-';
				cart_list.push_back(Cart(Vector2D(x, y),1));
			}
		}	
	}


	// std::vector<Cart>::const_iterator it2 = find_collision(cart_list);
	// if(it2 != cart_list.end()){
	// 	std::cout << "Cart collision found at " << it2->location << "\n";
	// }




	DrawTrack(track, cart_list);
	AdvanceTimeStep(track, cart_list);
	DrawTrack(track, cart_list);
	AdvanceTimeStep(track, cart_list);
	DrawTrack(track, cart_list);
	AdvanceTimeStep(track, cart_list);
	DrawTrack(track, cart_list);


	// std::cout << track[0][0] << "\n";
	// std::cout << track[0][1] << "\n";
	// std::cout << track[0][2] << "\n";
	// std::cout << track[0][3] << "\n";
	// std::cout << track[0][4] << "\n";
	// std::cout << track[0][5] << "\n";
	// std::cout << track[0][6] << "\n";

}



/*
	Things I learnt
		1) Scoped enums
		2) Trying to access an out of bounds element will sometimes just stop everything from happening.
		3) use const auto &i when doing range based loops, they are faster.

*/