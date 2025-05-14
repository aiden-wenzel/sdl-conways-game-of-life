#include <SDL3/SDL.h>
#include <utility>

#include "colony.hpp"

std::pair<int, int> get_mouse_pos(SDL_Event* event);
std::pair<int, int> mouse_to_index(const std::pair<int, int>& mouse_pos, float cell_size);
void render_mouse_cell(SDL_Renderer* renderer, const std::pair<int, int>& mouse_pos, float cell_size); 
void resurect_cells(const std::pair<int, int>& mouse_pos, Colony* colony, float cell_size);
