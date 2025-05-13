#include <iostream>
#include <SDL3/SDL.h>

#include "SDL_Utils.hpp"
#include "colony.hpp"

SDL_Window* initializeWindow(float width, float height) {
	// Create an SDL window
	SDL_Window* window = SDL_CreateWindow("Simple SDL2 Window",
			width, height, 0);
	if (window == NULL) {
		std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << "\n";
		SDL_Quit();
		exit(-1);
	}
	return window;
}

SDL_Renderer* initializeRenderer(SDL_Window* window) {
	SDL_Renderer* renderer = SDL_CreateRenderer(window, "gpu");

	if (renderer == NULL) {
		std::cout << "Renderer could not be created! SDL_Error:" << SDL_GetError() << "\n";
		SDL_Quit();
		exit(-2);
	}

	return renderer;
}

void draw_cell(SDL_Renderer* renderer, float cell_dim, float x, float y) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_FRect cell = {y, x, cell_dim, cell_dim};
	SDL_RenderFillRect(renderer, &cell);
}

void erase_cell(SDL_Renderer* renderer, float cell_dim, float x, float y) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_FRect cell = {y, x, cell_dim, cell_dim};
	SDL_RenderFillRect(renderer, &cell);
}

void draw_colony(SDL_Renderer* renderer, Colony* colony, float cell_size) {	
	for (int i = 0; i < colony->get_num_rows(); i++) {
		for (int j = 0; j < colony->get_num_cols(); j++) {
			if (colony->get_cell_at(i, j) == 1) {
				draw_cell(renderer,	cell_size, i*cell_size, j*cell_size);
			}
			else if(colony->get_cell_at(i, j) == 0) {
				erase_cell(renderer, cell_size, i*cell_size, j*cell_size);
			}
		}
	}
}
