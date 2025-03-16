#include <SDL3/SDL.h>
#include <utility>

std::pair<int, int> get_mouse_pos(SDL_Event* event);

std::pair<int, int> mouse_to_index(const std::pair<int, int>& mouse_pos, float cell_size);
