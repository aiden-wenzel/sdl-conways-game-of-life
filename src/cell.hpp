#pragma once

#include <SDL3/SDL.h>

class Cell {
public:
	// Constructors
	Cell();

	// Getters
	bool is_alive();

	// Setters

private:
	int alive;
};
