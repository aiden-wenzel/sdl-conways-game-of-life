#include <iostream>
#include <SDL3/SDL.h>

#include "SDL_Utils.hpp"

SDL_Window* initializeWindow(int width, int height) {
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
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		std::cout << "Renderer could not be created! SDL_Error:" << SDL_GetError() << "\n";
		SDL_Quit();
		exit(-2);
	}

	return renderer;
}
