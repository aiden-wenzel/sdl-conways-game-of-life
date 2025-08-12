#include <gtest/gtest.h>

#include "life/mouse.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Mouse, mouse_pos_to_index) {
	std::pair<int, int> mouse_pos = {15, 23};
	float cell_size = 10;
	std::pair<int, int> index = {2, 1};
	ASSERT_EQ(mouse_to_index(mouse_pos, cell_size), index);
}
