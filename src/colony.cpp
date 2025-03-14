#include <vector>


#include "colony.hpp"

// Constructor
Colony::Colony(int screen_width_in, int screen_height_in, int cell_size) {
	this->cell_size = cell_size;
	this->rows = screen_height_in/cell_size; 
	this->columns = screen_width_in/cell_size;
	this->underpopulation_limit = 2;
	this->overpopulation_limit = 3;
	this->resurection_limit = 3;
	initialize_cell_map();
	initialize_cells_to_inspect();
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

	initialize_cells_to_inspect();
}

void Colony::initialize_cell_map() {
	this->cell_map.resize(this->rows);

	std::vector<int> dummy(this->columns, 0);
	for (int i = 0; i < this->cell_map.size(); i++) {
		this->cell_map[i] = dummy;
	}
}

void Colony::initialize_cells_to_inspect() {
	std::vector<std::pair<int, int>> tmp;
	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < this->columns; col++) {
			if (this->cell_map[row][col] == 1) {
				this->cells_to_inspect.insert({row, col});
				tmp = this->get_neighbors(row, col);
				this->cells_to_inspect.insert(tmp.begin(), tmp.end());
			}
		}
	}
}

// Getters
int Colony::get_num_rows() { return this->rows; }
int Colony::get_num_cols() { return this->columns; }
int Colony::get_cell_at(int row, int column) { return this->cell_map[row][column]; }
int Colony::get_num_cells_to_investigate() {return this->cells_to_inspect.size();}
int Colony::get_num_cells_to_kill() {return this->cells_to_kill.size();}
int Colony::get_num_cells_to_resurect() {return this->cells_to_resurect.size();}
int Colony::get_cell_size() {return this->cell_size;}

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

int Colony::find_num_alive_neighbors(int row, int column) {

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

bool Colony::kill_cell(int row, int column) {
	int alive_neighbors = this->find_num_alive_neighbors(row, column);
	int current_status = this->cell_map[row][column];
	bool condition_1 = this->underpopulation_limit <= alive_neighbors;
	bool condition_2 = alive_neighbors <= this->overpopulation_limit;
	return !(condition_1 && condition_2) && current_status == 1;
}

bool Colony::resurect_cell(int row, int column) {
	int alive_neighbors = this->find_num_alive_neighbors(row, column);
	int current_status = this->cell_map[row][column];
	return alive_neighbors == this->resurection_limit && current_status == 0;
}

void Colony::add_cells_to_containers() {
	auto begin = this->cells_to_inspect.begin();
	auto end = this->cells_to_inspect.end();
	for (auto it = begin; it != end; it++) {
		if (resurect_cell(it->first, it->second)) {
			this->cells_to_resurect.push(*it);
		}	
		else if (kill_cell(it->first, it->second)) {
			this->cells_to_kill.push(*it);
		}
	}
	this->cells_to_inspect.clear();
}

void Colony::kill_cells() {
	while(!this->cells_to_kill.empty()) {
		std::pair<int, int> choord = this->cells_to_kill.front();
		this->cell_map[choord.first][choord.second] = 0;
		this->cells_to_kill.pop();
	}
}

void Colony::resurect_cells() {
	std::vector<std::pair<int, int>> inspect;
	while (!this->cells_to_resurect.empty()) {
		std::pair<int, int> choord = this->cells_to_resurect.front();
		this->cell_map[choord.first][choord.second] = 1;
		this->cells_to_resurect.pop();

		inspect = this->get_neighbors(choord.first, choord.second);

		for (int i = 0; i < inspect.size(); i++) {
			this->cells_to_inspect.insert(inspect[i]);
		}
	}
}
// Setters
void Colony::set_cell_at(int row, int column, int value) {
	this->cell_map[row][column] = value;
}
