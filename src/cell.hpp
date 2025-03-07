class Cell {
public:
	// Constructors
	Cell(int row_in, int column_in);

	// Getters
	int get_row();
	int get_column();
	bool is_alive();

	// Setters

private:
	int alive;
	int row;
	int column;
};
