#include <SDL3/SDL.h>

SDL_Window* initializeWindow(int width, int height);
SDL_Renderer* initializeRenderer(SDL_Window* window);

void draw_cell(SDL_Renderer* renderer, float cell_dim, float x, float y);
