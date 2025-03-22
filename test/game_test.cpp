#include <SDL3/SDL.h>
#include <vector>

#include "SDL_Utils.hpp"
#include "colony.hpp"
#include "game.hpp"

const float height = 900;
const float width = 900;
const float cell_size = 2;

int main() {
	Game game(width, height, cell_size);

	std::vector<std::vector<int>> bit_map = {
		{1, 1, 1},
		{1, 0, 1},
		{1, 0, 1},
	};
	
	int offset = 40;
	game.insert_cell_snippet(bit_map, offset);
	
	int quit = 0;
	SDL_Event event;
	SDL_SetRenderDrawColor(game.get_renderer(), 255, 255, 255, 0);
	SDL_RenderClear(game.get_renderer());

	while (!quit) {
		// Handle events
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_EVENT_QUIT) {
				quit = 1;
			}
		}
		SDL_RenderPresent(game.get_renderer());
		game.draw_colony();
	}
	
	SDL_DestroyWindow(game.get_window());
	SDL_Quit();

	return 0;

}
