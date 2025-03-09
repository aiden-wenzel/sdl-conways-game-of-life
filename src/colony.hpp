#pragma once
#include <vector>

class Cell;

class Colony {
public:
	// Constructors
	Colony(int screen_width_in, int screen_height_in);

	// Getters
	int getNumRows();
	int getNumCols();
	int getCellAt(int row, int column);

private:
	// Helper Functions
	void initializeCellMap();

	// Member Variables
	int rows;
	int columns;
	std::vector<std::vector<int>> cellMap;
};
