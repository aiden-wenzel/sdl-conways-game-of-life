#include <SDL3/SDL.h>

#include "cell.hpp"
#include "SDL_Utils.hpp"

const float height = 400;
const float width = height;

int main() {
	SDL_Window* window = initializeWindow(height, width);
	SDL_Renderer* renderer = initializeRenderer(window);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	draw_cell(renderer, 20, width/2, height/2);
	SDL_RenderPresent(renderer);

	int quit = 0;
	SDL_Event event;

	while (!quit) {
		// Handle events
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_EVENT_QUIT) {
				quit = 1;
			}
		}
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;

}
