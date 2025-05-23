#include <vector>


#include "colony.hpp"

/*----------Constructors----------*/
Colony::Colony(int rows_in, int columns_in) {
	this->rows = rows_in; 
	this->columns = columns_in;
	this->underpopulation_limit = 2;
	this->overpopulation_limit = 3;
	this->resurection_limit = 3;
	initialize_cell_map();
	initialize_alive_cells();
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

	initialize_alive_cells();
}

void Colony::initialize_cell_map() {
	this->cell_map.resize(this->rows);

	std::vector<int> dummy(this->columns, 0);
	for (int i = 0; i < this->cell_map.size(); i++) {
		this->cell_map[i] = dummy;
	}
}

void Colony::initialize_alive_cells() {
	std::vector<std::pair<int, int>> tmp;
	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < this->columns; col++) {
			if (this->cell_map[row][col] == 1) {
				this->alive_cells.insert({row, col});
			}
		}
	}
}

/*----------Getters----------*/
int Colony::get_num_rows() { return this->rows; }
int Colony::get_num_cols() { return this->columns; }
int Colony::get_cell_at(int row, int column) { return this->cell_map[row][column]; }
int Colony::get_num_cells_to_investigate() {return this->alive_cells.size();}
int Colony::get_num_cells_to_kill() {return this->cells_to_kill.size();}
int Colony::get_num_cells_to_resurect() {return this->cells_to_resurect.size();}

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

int Colony::get_num_alive_neighbors(int row, int column) {

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

/*----------Setters----------*/
void Colony::reset_colony() {
	for (int i = 0; i < this->cell_map.size(); i++) {
		for (int j = 0; j < this->cell_map[i].size(); j++) {
			this->set_cell_at(i, j, 0);
		}
	}
}
void Colony::set_cell_at(int row, int column, int value) {
	this->cell_map[row][column] = value;
	if (value == 1) {
		this->alive_cells.insert({row, column});
	}
}


bool Colony::kill_cell(int row, int column) {
	int alive_neighbors = this->get_num_alive_neighbors(row, column);
	int current_status = this->cell_map[row][column];
	bool condition_1 = this->underpopulation_limit <= alive_neighbors;
	bool condition_2 = alive_neighbors <= this->overpopulation_limit;
	return !(condition_1 && condition_2) && current_status == 1;
}

bool Colony::resurect_cell(int row, int column) {
	int alive_neighbors = this->get_num_alive_neighbors(row, column);
	int current_status = this->cell_map[row][column];
	return alive_neighbors == this->resurection_limit && current_status == 0;
}

void Colony::kill_cells() {
	for (int i = 0; i < this->cells_to_kill.size(); i++) {
		std::pair<int, int> choord = this->cells_to_kill[i];
		this->cell_map[choord.first][choord.second] = 0;
		this->alive_cells.erase({choord.first, choord.second});
	}
	this->cells_to_kill.clear();
}

void Colony::resurect_cells() {
	std::vector<std::pair<int, int>> inspect;

	for (int i = 0; i < this->cells_to_resurect.size(); i++) {
		std::pair<int, int> choord = this->cells_to_resurect[i];
		this->cell_map[choord.first][choord.second] = 1;
		this->alive_cells.insert({choord.first, choord.second});
	}
	this->cells_to_resurect.clear();
}

void Colony::update_colony() {
	this->add_cells_to_containers();
	this->kill_cells();
	this->resurect_cells();
}

void Colony::add_cells_to_containers() {
	for (auto it = this->alive_cells.begin(); it != this->alive_cells.end(); it++) {
		std::pair<int, int> curr_alive_cell = *it;	
		std::vector<std::pair<int, int>> neighbors = this->get_neighbors(curr_alive_cell.first, curr_alive_cell.second);

		if (resurect_cell(curr_alive_cell.first, curr_alive_cell.second)) {
			this->cells_to_resurect.push_back(*it);
		}
		else if (kill_cell(curr_alive_cell.first, curr_alive_cell.second)) {
			this->cells_to_kill.push_back(*it);
		}

		for (int i = 0; i < neighbors.size(); i++) {
			std::pair<int, int> tmp = neighbors[i];
			if (resurect_cell(tmp.first, tmp.second)) {
				this->cells_to_resurect.push_back(neighbors[i]);
			}
			else if (kill_cell(tmp.first, tmp.second)) {
				this->cells_to_kill.push_back(neighbors[i]);
			}
		}
	}
}
