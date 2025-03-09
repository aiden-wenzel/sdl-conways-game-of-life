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
