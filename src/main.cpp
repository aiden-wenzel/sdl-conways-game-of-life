#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "SDL_Utils.hpp"
#include "colony.hpp"
#include "mouse.hpp"

const float WIDTH = 800;
const float HEIGHT = 600;
const float cell_size = 10;

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Window* window = initializeWindow(WIDTH, HEIGHT);
	SDL_Renderer* renderer = initializeRenderer(window);

	Colony colony(HEIGHT/cell_size, WIDTH/cell_size);
	std::vector<std::vector<int>> bit_map = {
		{1, 1, 1},
		{1, 0, 1},
		{1, 0, 1},
	};
	int offset = 15;
	for (int i = 0; i < bit_map.size(); i++) {
		for (int j = 0; j < bit_map[i].size(); j++) {
			if (bit_map[i][j] == 1) {
				colony.set_cell_at(i+offset, j+offset, 1);
			}
		}
	}

	// Main loop flag
	int quit = 0;
	SDL_Event event;

	while (!quit) {
		// Handle events
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_EVENT_QUIT) {
				quit = 1;
			}
		}
		SDL_RenderPresent(renderer);
		colony.update_colony();
		draw_colony(renderer, &colony, cell_size);
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
