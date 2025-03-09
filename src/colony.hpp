#pragma once
#include <vector>

class Cell;

class Colony {
public:
	// Constructors
	Colony(int screen_width_in, int screen_height_in, int cell_size);

	// Getters
	int get_num_rows();
	int get_num_cols();
	int get_cell_at(int row, int column);

	// Setters
	void set_cell_at(int row, int column, int value);

private:
	// Helper Functions
	void initialize_cell_map();

	// Member Variables
	int rows;
	int columns;
	std::vector<std::vector<int>> cell_map;
};
