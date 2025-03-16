#include <SDL3/SDL.h>
#include <utility>

std::pair<int, int> get_mouse_pos(SDL_Event* event) {
	return {event->motion.x, event->motion.y};
}
