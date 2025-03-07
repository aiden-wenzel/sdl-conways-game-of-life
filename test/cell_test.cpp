#include <gtest/gtest.h>

#include "cell.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Cell, Constructor) {
	Cell test_cell;
	ASSERT_TRUE(!test_cell.is_alive());
}
