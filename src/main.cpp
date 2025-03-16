#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL3/SDL.h>

#include "SDL_Utils.hpp"
#include "colony.hpp"
#include "mouse.hpp"
#include "game.hpp"

const float WIDTH = 1080;
const float HEIGHT = 920;
const float cell_size = 10;

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
	Game game(WIDTH, HEIGHT);

	Colony colony(HEIGHT/cell_size, WIDTH/cell_size);

	// Main loop flag
	int quit = 0;
	SDL_Event event;
	std::pair<int, int> mouse_pos;

	bool in_start = true;

	while (!quit) {
		// Handle events
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_EVENT_QUIT) {
				quit = 1;
			}
			else if (event.type == SDL_EVENT_MOUSE_MOTION) {
				mouse_pos = get_mouse_pos(&event);
			}
			else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && in_start) {
				draw_cells(game.get_renderer(), mouse_pos, &colony, cell_size);
				if (0 <= mouse_pos.first && mouse_pos.first <= 80 && 0 <= mouse_pos.second && mouse_pos.second <=40 ) {
					in_start = false;
				}
			}
		}

		draw_colony(game.get_renderer(), &colony, cell_size);	
		if (!in_start) {
			colony.update_colony();
		}

		else {
			render_start_button(game.get_renderer(), {0, 0}, {80, 40});		
			render_mouse_cell(game.get_renderer(), mouse_pos, cell_size);
		}
		SDL_RenderPresent(game.get_renderer());
	}
	
	SDL_DestroyWindow(game.get_window());
	SDL_Quit();

	return 0;
}
