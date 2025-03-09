#include <gtest/gtest.h>

#include "colony.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Constructor, basic) {
	Colony colony(800, 400);
	ASSERT_EQ(colony.getNumCols(), 800/2);
	ASSERT_EQ(colony.getNumRows(), 400/2);
	
	for (int i = 0; i < colony.getNumRows(); i++) {
		for (int j = 0; j < colony.getNumCols(); j++) {
			ASSERT_EQ(colony.getCellAt(i, j), 0);
		}
	}
}
