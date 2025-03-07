#include "cell.hpp"

// Constructors
Cell::Cell(int row_in, int column_in) {
	this->row = row_in;
	this->column = column_in;
	this->alive = false;
}

// Getters
int Cell::get_row() {return this->row;}
int Cell::get_column() {return this->column;}
bool Cell::is_alive() {return this->alive;}

// Setters
