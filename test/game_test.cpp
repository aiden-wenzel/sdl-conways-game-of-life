#include <SDL3/SDL.h>
#include <vector>

#include "life/SDL_Utils.hpp"
#include "life/colony.hpp"

const float height = 900;
const float width = 900;
const float cell_size = 2;

int main() {
	SDL_Window* window = initializeWindow(height, width);
	SDL_Renderer* renderer = initializeRenderer(window);

	Colony colony(height/cell_size, width/cell_size);
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
