#include <SDL3/SDL.h>
#include <utility>
#include <cmath>

#include "life/mouse.hpp"

std::pair<int, int> get_mouse_pos(SDL_Event* event) {
	return {event->motion.x, event->motion.y};
}

std::pair<int, int> mouse_to_index(const std::pair<int, int>& mouse_pos, float cell_size) {
	return {mouse_pos.second/cell_size, mouse_pos.first/cell_size};
}

void render_mouse_cell(SDL_Renderer* renderer, const std::pair<int, int>& mouse_pos, float cell_size) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 129, 0);

	float x = floor(mouse_pos.second/cell_size);
	float y = floor(mouse_pos.first/cell_size);

	x *= cell_size;
	y *= cell_size;

	SDL_FRect cell = {y, x, cell_size, cell_size};
	SDL_RenderFillRect(renderer, &cell);
}

void resurect_cells(const std::pair<int, int>& mouse_pos, Colony* colony, float cell_size) {
	std::pair<int, int> indicies = mouse_to_index(mouse_pos, cell_size);
	colony->set_cell_at(indicies.first, indicies.second, 1);
}
