#include <SDL3/SDL.h>
#include <iostream>

#include "game.hpp"

Game::Game(float width, float height, float cell_size) {
	this->window = this->initializeWindow(width, height);
	this->renderer = this->initializeRenderer(this->window);	
	this->cell_size = cell_size;

	this->colony = new Colony(height/cell_size, width/cell_size);
}
Game::~Game() {
	std::cout << "Destroying Colony\n";
	delete this->colony;
}

SDL_Renderer* Game::get_renderer() {return this->renderer;}
SDL_Window* Game::get_window() {return this->window;}

SDL_Window* Game::initializeWindow(float width, float height) {
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

SDL_Renderer* Game::initializeRenderer(SDL_Window* window) {
	SDL_Renderer* renderer = SDL_CreateRenderer(window, "gpu");

	if (renderer == NULL) {
		std::cout << "Renderer could not be created! SDL_Error:" << SDL_GetError() << "\n";
		SDL_Quit();
		exit(-2);
	}

	return renderer;
}

