#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window* initializeWindow(int width, int height); 
SDL_Renderer* initializeRenderer(SDL_Window* window);

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Window* window = initializeWindow(WIDTH, HEIGHT);
	SDL_Renderer* renderer = initializeRenderer(window);

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
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

SDL_Window* initializeWindow(int width, int height) {
	// Create an SDL window
	SDL_Window* window = SDL_CreateWindow("Simple SDL2 Window",
			width, height, 0);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}
	return window;

}

SDL_Renderer* initializeRenderer(SDL_Window* window) {
	SDL_Renderer* renderer = SDL_CreateRenderer(window, "gpu");

	if (renderer == NULL) {
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(-2);
	}

	return renderer;
}
