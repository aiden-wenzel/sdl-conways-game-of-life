#include <SDL3/SDL.h>
#include <iostream>

#include "life/SDL_Utils.hpp"
#include "life/mouse.hpp"

const float height = 900;
const float width = 900;

int main() {
	SDL_Window* window = initializeWindow(height, width);
	SDL_Renderer* renderer = initializeRenderer(window);

	int quit = 0;
	SDL_Event event;
	
	std::pair<int, int> mouse_pos;
	while (!quit) {
		// Handle events
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_EVENT_QUIT) {
				quit = 1;
			}
			else if (event.type == SDL_EVENT_MOUSE_MOTION) {
				mouse_pos = get_mouse_pos(&event);
			}
		}

		std::cout << mouse_pos.first << ", " << mouse_pos.second << '\n';
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;

}
