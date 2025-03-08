#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#include "cell.hpp"

// Constructors
Cell::Cell() {
	this->alive = false;
}

// Getters
bool Cell::is_alive() {return this->alive;}

void draw_cell(SDL_Renderer* renderer, float cell_dim, float x, float y) {
	SDL_FRect cell = {x, y, cell_dim, cell_dim};
	SDL_RenderFillRect(renderer, &cell);
}
