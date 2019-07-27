// TestConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>


struct ID
{
	int x;
	int y;
	int size;
};

bool operator==(const ID& lhs, const ID& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.size == rhs.size;
}

bool operator<(const ID& lhs, const ID& rhs)
{

	if (lhs.x == rhs.x) {
		if (lhs.y == rhs.y) {
			return  lhs.size < rhs.size;
		}
		else return lhs.y < rhs.y;
	}
	else return lhs.x < rhs.x;
}

int power_level(const int& x, const int& y, const int& serial_number) {
	return ((((10 + x) * y + serial_number) * (10 + x) / 100) % 10) - 5;
}

int main()
{

	int serial_number = 3999;

	int power_grid[300][300];
	int max_grid_size = 300;

	for (int x = 0; x < max_grid_size; x++) {
		for (int y = 0; y < max_grid_size; y++) {
			power_grid[x][y] = power_level(x + 1, y + 1, serial_number);
		}
	}


	//
	//	Part one
	//

	int power_sum = 0;
	int max_power_sum = 0;
	ID max_power_id;
	for (int x = 0; x < max_grid_size - 3; x++) {
		for (int y = 0; y < max_grid_size - 3; y++) {

			power_sum = 0;

			for (int i = x; i < x + 3; i++) {
				for (int j = y; j < y + 3; j++) {
					power_sum += power_grid[i][j];
				}
			}

			if (power_sum > max_power_sum) {
				max_power_sum = power_sum;
				max_power_id = { x + 1,y + 1,3 };
			}

		}
	}

	std::cout << "Part one ID (including width) : " << max_power_id.x << "," << max_power_id.y << "," << max_power_id.size << "\n";



	//
	//	Part two
	//

	max_power_sum = 0;
	int max_width, max_coord;
	for (int x = 0; x < max_grid_size; x++) {
		for (int y = 0; y < max_grid_size; y++) {
			power_sum = 0;
			max_coord = std::max(x, y);
			max_width = max_grid_size - max_coord;

			for (int width = 1; width <= max_width; width++) {

				for (int i = x; i < x + width; i++) {
					for (int j = y; j < y + width; j++) {
						power_sum += power_grid[i][j];
					}
				}
				if (power_sum > max_power_sum) {
					max_power_sum = power_sum;
					max_power_id = { x + 1,y + 1,width };
				}
			}
		}
	}

	// 224,222,27
	std::cout << "Part two ID (including width) : " << max_power_id.x << "," << max_power_id.y << "," << max_power_id.size << "\n";

	return 0;
}
