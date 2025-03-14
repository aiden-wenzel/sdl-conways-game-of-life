#pragma once
#include <vector>
#include <unordered_set>
#include <queue>

class Cell;
class SDL_Renderer;

struct PairHash {
public:
	template <typename T, typename U>
		std::size_t operator()(const std::pair<T, U> &x) const
		{
			return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
		}
};

class Colony {
public:
	/*----------Constructors----------*/
	Colony(int screen_width_in, int screen_height_in, int cell_size);
	Colony(const std::vector<std::vector<int>>& bit_map);

	/*----------Getters----------*/
	int get_num_rows();
	int get_num_cols();
	int get_cell_at(int row, int column);
	int get_num_cells_to_investigate();
	int get_num_cells_to_kill();
	int get_num_cells_to_resurect();
	int get_cell_size();

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

	bool kill_cell(int row, int column);
	bool resurect_cell(int row, int column);
	void add_cells_to_containers();
	void kill_cells();
	void resurect_cells();

	/*----------Setters----------*/
	void set_cell_at(int row, int column, int value);
	void initialize_cells_to_inspect();

private:
	/**
	 * Goes through entire cell map and adds both
	 * cells with the value 1 and their adjacent neighbors to the cell stack.
	 */

	void initialize_cell_map();

	// Map Variables
	int rows;
	int columns;
	int cell_size;
	std::vector<std::vector<int>> cell_map;
	
	// Game Rules
	int overpopulation_limit;
	int underpopulation_limit;
	int resurection_limit;

	// Containers
	std::unordered_set<std::pair<int, int>, PairHash> cells_to_inspect;
	std::queue<std::pair<int, int>> cells_to_kill;
	std::queue<std::pair<int, int>> cells_to_resurect;

	friend void update_cells(SDL_Renderer* renderer, Colony* colony);
	friend void draw_colony(SDL_Renderer* renderer, Colony* colony); 
};
