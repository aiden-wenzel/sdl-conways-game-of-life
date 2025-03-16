#pragma once

#include <SDL3/SDL.h>

class Game {
public:
	Game(float width, float height);

	SDL_Renderer* get_renderer();
	SDL_Window* get_window();

private:
	SDL_Window* initializeWindow(float width, float height);
	SDL_Renderer* initializeRenderer(SDL_Window* window);

	SDL_Renderer* renderer;
	SDL_Window* window;
};
