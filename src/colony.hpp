#pragma once
#include <vector>

class Cell;

class Colony {
public:
	// Constructors
	Colony(int screen_width_in, int screen_height_in);

	// Getters
	int get_num_rows();
	int get_num_cols();
	int get_cell_at(int row, int column);

private:
	// Helper Functions
	void initialize_cell_map();

	// Member Variables
	int rows;
	int columns;
	std::vector<std::vector<int>> cellMap;
};
