#include "cell.hpp"
#include "colony.hpp"

Colony::Colony(int screen_width_in, int screen_height_in) {
	const int CELL_SIZE = 2;
	this->rows = screen_width_in/CELL_SIZE; 
	this->columns = screen_height_in/CELL_SIZE;
	initialize_cell_map();
}

void Colony::initialize_cell_map() {
	this->cell_map.resize(this->rows);

	std::vector<Cell> dummy(this->columns);
	for (int i = 0; i < this->cell_map.size(); i++) {
		this->cell_map[i] = dummy;
	}
}
