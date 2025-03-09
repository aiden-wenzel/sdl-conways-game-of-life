#include <gtest/gtest.h>

#include "colony.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Constructor, basic) {
	Colony colony(800, 400);
	ASSERT_EQ(colony.get_num_cols(), 800/2);
	ASSERT_EQ(colony.get_num_rows(), 400/2);
	
	for (int i = 0; i < colony.get_num_rows(); i++) {
		for (int j = 0; j < colony.get_num_cols(); j++) {
			ASSERT_EQ(colony.get_cell_at(i, j), 0);
		}
	}
}
