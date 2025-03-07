#pragma once
#include <vector>

class Cell;

class Colony {
public:
	// Constructors
	Colony(int screen_width_in, int screen_height_in);

private:
	// Helper Functions
	void initialize_cell_map();

	// Member Variables
	int rows;
	int columns;
	std::vector<std::vector<Cell>> cell_map;
};
