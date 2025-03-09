#pragma once
#include <vector>

class Cell;

class Colony {
public:
	/*----------Constructors----------*/
	Colony(int screen_width_in, int screen_height_in, int cell_size);
	Colony(const std::vector<std::vector<int>>& bit_map);

	/*----------Getters----------*/
	int get_num_rows();
	int get_num_cols();
	int get_cell_at(int row, int column);

	/**
	 * Return the choordinates of adjacent cells as {row, column}.
	 *
	 * @param row Row of the cell.
	 * @param column Column of the cell.
	 *
	 * @return choordinate pairs of all adjacent cells.
	 */
	std::vector<std::pair<int, int>> get_neighbors(int row, int column); 

	/**	
	 * Return the number of alive adjacent cells. 
	 * A cell is alive if their value is equal to 1.
	 *
	 * @param row Row of the cell.
	 * @param column Column of the cell.
	 *
	 * @return integer sum of alive cells.
	 */
	int find_num_alive_neighbors(int row, int column);

	/**
	 * Retrun true if the cell at (row, column) should die.
	 * 
	 * @param row Row of the cell.
	 * @param column Column of the cell.
	 * 
	 * @return true if the cell should die.
	 */
	bool determine_fate(int row, int column);

	/*----------Setters----------*/
	void set_cell_at(int row, int column, int value);

private:
	void initialize_cell_map();

	// Map Variables
	int rows;
	int columns;
	std::vector<std::vector<int>> cell_map;
	
	// Game Rules
	int overpopulation_limit;
	int underpopulation_limit;
	int resurection_limit;
};
