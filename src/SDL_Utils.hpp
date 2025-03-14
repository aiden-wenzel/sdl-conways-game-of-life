#include <SDL3/SDL.h>

#include "colony.hpp"

SDL_Window* initializeWindow(float width, float height);
SDL_Renderer* initializeRenderer(SDL_Window* window);

void draw_cell(SDL_Renderer* renderer, float cell_dim, float x, float y);
void erase_cell(SDL_Renderer* renderer, float cell_dim, float x, float y);

void draw_colony(SDL_Renderer* renderer, Colony* colony);
void update_cells(SDL_Renderer* renderer, Colony* colony);
