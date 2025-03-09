#include "cell.hpp"
#include "colony.hpp"

// Constructor
Colony::Colony(int screen_width_in, int screen_height_in) {
	const int CELL_SIZE = 2;
	this->rows = screen_height_in/CELL_SIZE; 
	this->columns = screen_width_in/CELL_SIZE;
	initialize_cell_map();
}

void Colony::initialize_cell_map() {
	this->cellMap.resize(this->rows);

	std::vector<int> dummy(this->columns, 0);
	for (int i = 0; i < this->cellMap.size(); i++) {
		this->cellMap[i] = dummy;
	}
}

// Getters
int Colony::get_num_rows() {
	return this->rows;
}

int Colony::get_num_cols() {
	return this->columns;
}

int Colony::get_cell_at(int row, int column) {
	return this->cellMap[row][column];
}
