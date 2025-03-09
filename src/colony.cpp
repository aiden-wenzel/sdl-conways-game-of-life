#include "cell.hpp"
#include "colony.hpp"

// Constructor
Colony::Colony(int screen_width_in, int screen_height_in, int cell_size) {
	this->rows = screen_height_in/cell_size; 
	this->columns = screen_width_in/cell_size;
	initialize_cell_map();
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

// Setters
void Colony::set_cell_at(int row, int column, int value) {
	this->cell_map[row][column] = value;
}
