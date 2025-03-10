#include <vector>


#include "cell.hpp"
#include "colony.hpp"

// Constructor
Colony::Colony(int screen_width_in, int screen_height_in, int cell_size) {
	this->rows = screen_height_in/cell_size; 
	this->columns = screen_width_in/cell_size;
	this->underpopulation_limit = 2;
	this->overpopulation_limit = 3;
	this->resurection_limit = 3;
	initialize_cell_map();
}

Colony::Colony(const std::vector<std::vector<int>>& bit_map) {
	this->rows = bit_map.size();
	this->columns = bit_map[0].size();
	this->underpopulation_limit = 2;
	this->overpopulation_limit = 3;
	this->resurection_limit = 3;

	initialize_cell_map();

	for (int i = 0; i < bit_map.size(); i++) {
		for (int j = 0; j < bit_map[i].size(); j++) {
			this->cell_map[i][j] = bit_map[i][j];
		}
	}
}

void Colony::initialize_cell_map() {
	this->cell_map.resize(this->rows);

	std::vector<int> dummy(this->columns, 0);
	for (int i = 0; i < this->cell_map.size(); i++) {
		this->cell_map[i] = dummy;
	}
}

// Getters
int Colony::get_num_rows() { return this->rows; }
int Colony::get_num_cols() { return this->columns; }
int Colony::get_cell_at(int row, int column) { return this->cell_map[row][column]; }

std::vector<std::pair<int,int>> Colony::get_neighbors(int row, int column) {
	std::vector<std::pair<int, int>> ans;

	bool top_boarder = row == 0;
	bool bottom_boarder = row == this->rows-1;
	bool left_boarder = column == 0;
	bool right_boarder = column == this->columns-1;

	int last_column = this->columns-1;
	int last_row = this->rows-1;

	if (top_boarder && left_boarder) {
		ans.push_back({0, 1});
		ans.push_back({1, 0});
		ans.push_back({1, 1});
	}

	else if ( top_boarder && right_boarder) {
		ans.push_back({0, last_column-1});
		ans.push_back({1, last_column-1});
		ans.push_back({1, last_column});
	}

	// Bottom Left Corner
	else if (bottom_boarder && left_boarder) {
		ans.push_back({last_row-1, 0});
		ans.push_back({last_row-1, 1});
		ans.push_back({last_row, 1});
	}

	// Bottom Right Corner
	else if (bottom_boarder && right_boarder) {
		ans.push_back({last_row, last_column-1});
		ans.push_back({last_row-1, last_column-1});
		ans.push_back({last_row-1, last_column});
	}

	// Top Boarder
	else if (top_boarder) {
		ans.push_back({0, column-1});
		ans.push_back({0, column+1});
		int bottom_row = 1;
		for (int i = 0; i < 3; i++) {
			ans.push_back({1, column-1+i});
		}
	}

	// Bottom Boarder
	else if(bottom_boarder) {
		ans.push_back({last_row, column-1});
		ans.push_back({last_row, column+1});
		int top_row = this->rows-2;
		for (int i = 0; i < 3; i++) {
			ans.push_back({top_row, column-1+i});
		}
	}

	// Left Boarder
	else if(left_boarder) {
		ans.push_back({row-1, 0});
		ans.push_back({row+1, 0});
		int right_col = 1;
		for (int i = 0; i < 3; i++) {
			ans.push_back({row-1+i, right_col});
		}
	}

	// Right Boarder
	else if(right_boarder) {
		ans.push_back({row-1, 0});
		ans.push_back({row+1, 0});
		int left_col = this->columns-2;
		for (int i = 0; i < 3; i++) {
			ans.push_back({row-1+i, left_col});
		}
	}
	
	// Not Boarder
	else {
		ans.push_back({row, column-1});
		ans.push_back({row, column+1});
		for (int i = 0; i < 3; i++) {
			ans.push_back({row+1, column-1+i});
		}
		for (int i = 0; i < 3; i++) {
			ans.push_back({row-1, column-1+i});
		}
	}

	return ans;
}

int Colony::find_num_alive_neighbors(int row, int column) {

	std::vector<std::pair<int, int>> choords = this->get_neighbors(row, column);	

	// Count number of ones.
	int count = 0;
	for (int i = 0; i < choords.size(); i++) {
		if (this->get_cell_at(choords[i].first, choords[i].second) == 1) {
			count++;
		}
	}

	return count;
}

bool Colony::determine_fate(int row, int column) {
	int alive_neighbors = this->find_num_alive_neighbors(row, column);
	bool condition_1 = this->underpopulation_limit <= alive_neighbors;
	bool condition_2 = alive_neighbors <= this->overpopulation_limit;
	return !(condition_1 && condition_2);
}

// Setters
void Colony::set_cell_at(int row, int column, int value) {
	this->cell_map[row][column] = value;
}
