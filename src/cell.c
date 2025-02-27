#include "cell.h"

void initialize_cell(Cell* cell_in, int row_in, int column_in) {
	cell_in->row = row_in;
	cell_in->column = column_in;
	cell_in->is_alive = 0;
	cell_in->is_boarder = 0;
}
