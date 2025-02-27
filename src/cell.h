struct Cell {
	int is_alive;
	int is_boarder;
	int row;
	int column;
	int screen_coordinates[2];
};
typedef struct Cell Cell;

void initialize_cell(Cell* cell_in, int row_in, int column_in); 
