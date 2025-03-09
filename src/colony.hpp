#pragma once
#include <vector>

class Cell;

class Colony {
public:
	// Constructors
	Colony(int screen_width_in, int screen_height_in, int cell_size);
	Colony(const std::vector<std::vector<int>>& bit_map);

	// Getters
	int get_num_rows();
	int get_num_cols();
	int get_cell_at(int row, int column);

	std::vector<std::pair<int, int>> get_neighbors(int row, int column); 
	int find_num_alive_neighbors(int row, int column);

	/*
	return true if cell at <row>, <column> should die.
	*/
	bool determine_fate(int row, int column);

	// Setters
	void set_cell_at(int row, int column, int value);

private:
	// Helper Functions
	void initialize_cell_map();

	// Member Variables
	int rows;
	int columns;
	int overpopulation_limit;
	int underpopulation_limit;
	int resurection_limit;
	std::vector<std::vector<int>> cell_map;
};
