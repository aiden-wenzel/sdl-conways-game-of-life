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

void draw_cell(SDL_Renderer* renderer, float cell_dim, float x, float y);
