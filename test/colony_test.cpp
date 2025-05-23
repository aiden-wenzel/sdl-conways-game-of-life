#include <gtest/gtest.h>

#include "colony.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Colony, Constructor_Basic) {
	int num_rows = 200;
	int num_cols = 400;
	Colony colony(num_rows, num_cols);

	ASSERT_EQ(colony.get_num_cols(), num_cols);
	ASSERT_EQ(colony.get_num_rows(), num_rows);
	
	for (int i = 0; i < colony.get_num_rows(); i++) {
		for (int j = 0; j < colony.get_num_cols(); j++) {
			ASSERT_EQ(colony.get_cell_at(i, j), 0);
		}
	}
}

TEST(Colony, Constructor_Bit_Map) {
	std::vector<std::vector<int>> bit_map = {
		{0, 1, 0},
		{1, 1, 1},
		{1, 0, 0}
	};

	Colony colony(bit_map);

	for (int i = 0; i < bit_map.size(); i++) {
		for (int j = 0; j < bit_map[i].size(); j++) {
			ASSERT_EQ(colony.get_cell_at(i, j), bit_map[i][j]);
		}
	}
}

TEST(Colony, Set_Cell) {
	int screen_width = 3;
	int screen_height = 3;
	int cell_size = 1;

	Colony colony(screen_width/cell_size, screen_height/cell_size);

	colony.set_cell_at(0, 0, 15);
	ASSERT_EQ(colony.get_cell_at(0, 0), 15);

	colony.set_cell_at(2, 2, 1);
	ASSERT_EQ(colony.get_cell_at(2, 2), 1);
}

TEST(Colony, Count_Num_Alive_Neighbors) {
	std::vector<std::vector<int>> bit_map = {
		{0, 1, 0, 1, 0},
		{1, 1, 1, 1, 1},
		{0, 1, 1, 0, 0},
		{0, 0, 0, 1, 0},
		{1, 1, 0, 1, 0}
	};

	Colony colony(bit_map);

	int column, row;
	int expected_count;
	
	// Top Left
	column = 0;
	row = 0;
	expected_count = 3;
	ASSERT_EQ(colony.get_num_alive_neighbors(row, column), expected_count);

	// Top Right
	column = 4;
	row = 0;
	expected_count = 3;
	ASSERT_EQ(colony.get_num_alive_neighbors(row, column), expected_count);
	
	// Bottom Left
	column = 0;
	row = 4;
	expected_count = 1;
	ASSERT_EQ(colony.get_num_alive_neighbors(row, column), expected_count);

	// Bottom Right
	column = 4;
	row = 4;
	expected_count = 2;
	ASSERT_EQ(colony.get_num_alive_neighbors(row, column), expected_count);

	// Top Boarder
	column = 1;
	row = 0;
	expected_count = 3;
	ASSERT_EQ(colony.get_num_alive_neighbors(row, column), expected_count);
	
	// Bottom Boarder
	column = 1;
	row = 4;
	expected_count = 1;
	ASSERT_EQ(colony.get_num_alive_neighbors(row, column), expected_count);

	// Left Boarder
	column = 0;
	row = 1;
	expected_count = 3;
	ASSERT_EQ(colony.get_num_alive_neighbors(row, column), expected_count);

	// Right Boarder
	column = 4;
	row = 1;
	expected_count = 2;
	ASSERT_EQ(colony.get_num_alive_neighbors(row, column), expected_count);

	// General Case
	column = 2;
	row = 2;
	expected_count = 5;
	ASSERT_EQ(colony.get_num_alive_neighbors(row, column), expected_count);
}

TEST(Colony, determine_fate) {
	std::vector<std::vector<int>> bit_map = {
		{0, 1, 0, 1, 0},
		{1, 1, 1, 1, 1},
		{0, 1, 1, 0, 0},
		{0, 0, 0, 1, 0},
		{1, 1, 0, 0, 0}
	};
	
	Colony colony(bit_map);

	int row, column;
	
	// Cell should die by overpopulation.
	row = 1;
	column = 1;
	ASSERT_TRUE(colony.kill_cell(row, column));

	// Cell should not be changed.
	row = 4;
	column = 4;
	ASSERT_FALSE(colony.kill_cell(row, column) || colony.resurect_cell(row, column));

	// Cell should not be changed.
	row = 4;
	column = 2;
	ASSERT_FALSE(colony.kill_cell(row, column) || colony.resurect_cell(row, column));
}

TEST(Colony, initialize_cells_to_investigate) {
	std::vector<std::vector<int>> bit_map = {
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 1, 0, 0}
	};

	int num_ones = 2;
	int num_adjacent = 6;
	Colony colony(bit_map);
	ASSERT_EQ(colony.get_num_cells_to_investigate(), num_ones+num_adjacent);
}

TEST(Colony, kill_resurect_cell) {
	std::vector<std::vector<int>> bit_map = {
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 1, 0, 0}
	};

	Colony colony(bit_map);

	ASSERT_TRUE(colony.kill_cell(3, 1) && colony.kill_cell(3, 2));
	ASSERT_FALSE(colony.kill_cell(2, 1));
}

TEST(Colony, kill_and_resurect_cells) {
	std::vector<std::vector<int>> bit_map = {
		{0, 0, 0},
		{1, 1, 1},
		{0, 1, 1},
	};

	std::vector<std::vector<int>> next_1 = {
		{0, 1, 0},
		{1, 0, 1},
		{1, 0, 1},
	};

	std::vector<std::vector<int>> next_2 = {
		{0, 1, 0},
		{1, 0, 1},
		{0, 0, 0},
	};

	std::vector<std::vector<int>> next_3 = {
		{0, 1, 0},
		{0, 1, 0},
		{0, 0, 0},
	};

	std::vector<std::vector<int>> next_4 = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	};

	Colony colony(bit_map);
	using std::vector;
	vector<vector<vector<int>>> order = {bit_map, next_1, next_2, next_3, next_4};
	
	for (int i = 0; i < order.size(); i++) {
		ASSERT_EQ(colony.cell_map, order[i]);
		colony.update_colony();
	}
}

TEST(Colony_Private, add_cells_to_containers) {
	std::vector<std::vector<int>> bit_map = {
		{0, 0, 0},
		{1, 1, 1},
		{0, 1, 1},
	};

	std::vector<std::vector<int>> next_1 = {
		{0, 1, 0},
		{1, 0, 1},
		{1, 0, 1},
	};

	Colony colony(bit_map);
	colony.add_cells_to_containers();

	std::unordered_set<std::pair<int, int>, PairHash> cells_to_resurect;	
	cells_to_resurect.insert({0, 1});
	cells_to_resurect.insert({2, 0});

	for (int i = 0; i < colony.cells_to_resurect.size(); i++) {
		ASSERT_TRUE(cells_to_resurect.find({colony.cells_to_resurect[i]}) != cells_to_resurect.end());
	}

	std::unordered_set<std::pair<int, int>, PairHash> cells_to_kill;	
	cells_to_kill.insert({1, 1});
	cells_to_kill.insert({2, 1});
	for (int i = 0; i < colony.cells_to_kill.size(); i++) {
		ASSERT_TRUE(cells_to_kill.find({colony.cells_to_kill[i]}) != cells_to_kill.end());
	}

	
}
