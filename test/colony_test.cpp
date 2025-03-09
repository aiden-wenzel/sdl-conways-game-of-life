#include <gtest/gtest.h>

#include "colony.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Colony, Constructor_Basic) {
	int screen_width = 800;
	int screen_height = 400;
	int cell_size = 2;

	Colony colony(screen_width, screen_height, cell_size);
	ASSERT_EQ(colony.get_num_cols(), screen_width/cell_size);
	ASSERT_EQ(colony.get_num_rows(), screen_height/cell_size);
	
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

	Colony colony(screen_width, screen_height, cell_size);

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
	ASSERT_EQ(colony.find_num_alive_neighbors(row, column), expected_count);

	// Top Right
	column = 4;
	row = 0;
	expected_count = 3;
	ASSERT_EQ(colony.find_num_alive_neighbors(row, column), expected_count);
	
	// Bottom Left
	column = 0;
	row = 4;
	expected_count = 1;
	ASSERT_EQ(colony.find_num_alive_neighbors(row, column), expected_count);

	// Bottom Right
	column = 4;
	row = 4;
	expected_count = 2;
	ASSERT_EQ(colony.find_num_alive_neighbors(row, column), expected_count);

	// Top Boarder
	column = 1;
	row = 0;
	expected_count = 3;
	ASSERT_EQ(colony.find_num_alive_neighbors(row, column), expected_count);
	
	// Bottom Boarder
	column = 1;
	row = 4;
	expected_count = 1;
	ASSERT_EQ(colony.find_num_alive_neighbors(row, column), expected_count);

	// Left Boarder
	column = 0;
	row = 1;
	expected_count = 3;
	ASSERT_EQ(colony.find_num_alive_neighbors(row, column), expected_count);

	// Right Boarder
	column = 4;
	row = 1;
	expected_count = 2;
	ASSERT_EQ(colony.find_num_alive_neighbors(row, column), expected_count);

	// General Case
	column = 2;
	row = 2;
	expected_count = 5;
	ASSERT_EQ(colony.find_num_alive_neighbors(row, column), expected_count);
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
	ASSERT_TRUE(colony.determine_fate(row, column));

	// Cell should die by underpopultion.
	row = 4;
	column = 4;
	ASSERT_TRUE(colony.determine_fate(row, column));

	// Cell should not be changed.
	row = 4;
	column = 2;
	ASSERT_FALSE(colony.determine_fate(row, column));
}
