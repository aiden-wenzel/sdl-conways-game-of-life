#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#include "cell.hpp"

// Constructors
Cell::Cell() {
	this->alive = false;
}

// Getters
bool Cell::is_alive() {return this->alive;}

