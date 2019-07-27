#include <vector>
#include <iostream>
#include <algorithm>

//
//		This one runs very slow in debug mode, consider running in release to get the answer quicker
//


struct ID
{
	int x;
	int y;
	int size;
};

int sum_area(const int& x, const int& y, const int& width, const std::vector<std::vector<int>> & grid) {

	int power_sum = 0;

	for (int i = x; i < x + width; i++) {
		for (int j = y; j < y + width; j++) {
			power_sum += grid[i][j];
		}
	}

	return power_sum;
}


int power_level(const int& x, const int& y, const int& serial_number) {
	return ((((10 + x) * y + serial_number) * (10 + x) / 100) % 10) - 5;
}

int main()
{

	int serial_number = 3999;
	int max_grid_size = 300;

	std::vector<std::vector<int>> power_grid;

	power_grid.resize(max_grid_size);
	for (auto& vi : power_grid)
		vi.resize(max_grid_size);

	for (int x = 0; x < max_grid_size; x++) {
		for (int y = 0; y < max_grid_size; y++) {
			power_grid[x][y] = power_level(x + 1, y + 1, serial_number);
		}
	}

	//
	//	Part one
	//

	int area = 0;
	int max_power_sum = 0;
	ID max_power_id;
	for (int x = 0; x < max_grid_size - 3; x++) {
		for (int y = 0; y < max_grid_size - 3; y++) {
			
			area = sum_area(x, y, 3, power_grid);
			if (area > max_power_sum) {
				max_power_sum = area;
				max_power_id = { x + 1,y + 1,3 };
			}
		}
	}

	std::cout << "Part one ID (including width) : " << max_power_id.x << "," << max_power_id.y << "," << max_power_id.size << "\n";



	//
	//	Part two
	//

	area = 0;
	max_power_sum = 0;
	int max_width, max_coord;
	for (int x = 0; x < max_grid_size; x++) {
		for (int y = 0; y < max_grid_size; y++) {

			max_coord = std::max(x, y);
			max_width = max_grid_size - max_coord;

			for (int width = 1; width <= max_width; width++) {

				area = sum_area(x, y, width, power_grid);

				if (area > max_power_sum) {
					max_power_sum = area;
					max_power_id = { x + 1, y + 1, width };
				}

			}
		}
	}


	std::cout << "Part two ID (including width) : " << max_power_id.x << "," << max_power_id.y << "," << max_power_id.size << "\n";

	return 0;
}


/*

	Things I've learnt
		Again, be careful when using normal arrays. In this case a [300][300] array was nearly enough to cause
		stack overflow according to visual studio
		Sometimes things don't work for any obvious reason


*/