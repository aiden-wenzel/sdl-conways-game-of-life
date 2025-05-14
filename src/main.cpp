#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL3/SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include "SDL_Utils.hpp"
#include "colony.hpp"
#include "mouse.hpp"
#include "game.hpp"

const float WIDTH = 1080;
const float HEIGHT = 920;
const float cell_size = 20;

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	Game game(WIDTH, HEIGHT, cell_size);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImGui_ImplSDL3_InitForSDLRenderer(game.get_window(), game.get_renderer());
	ImGui_ImplSDLRenderer3_Init(game.get_renderer());

	// Main loop flag
	int quit = 0;
	SDL_Event event;
	std::pair<int, int> mouse_pos;

	bool in_start = true;
	bool mouse_held = false;
	bool restart = false;
	bool hovering;

	while (!quit) {
		// Handle events
		while (SDL_PollEvent(&event) != 0) {
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT) {
				quit = 1;
			}
			if (event.type == SDL_EVENT_MOUSE_MOTION) {
				mouse_pos = get_mouse_pos(&event);
			}
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				mouse_held = true;
			}
			if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
				mouse_held = false;
			}
		}
		hovering = io.WantCaptureMouse;

		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Hello, world!");
		if (ImGui::Button("Start")) {
			in_start = false;
		}
		else if (ImGui::Button("Restart")) {
			restart = true;
			in_start = false;
		}

		ImGui::End();
		ImGui::Render();
		
		if (restart) {
			game.get_colony()->reset_colony();
			restart = false;
			in_start = true;
		}
		else if (!in_start) {
			game.get_colony()->update_colony();
		}

		// Render
		SDL_SetRenderDrawColor(game.get_renderer(), 255, 255, 255, 255);
		SDL_RenderClear(game.get_renderer());

		game.draw_colony();

		SDL_SetRenderScale(game.get_renderer(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), game.get_renderer());

		if (in_start && !hovering) {
			render_mouse_cell(game.get_renderer(), mouse_pos, cell_size);
			if (mouse_held) {
				draw_cells(game.get_renderer(), mouse_pos, game.get_colony(), cell_size);
			}
		}

		SDL_RenderPresent(game.get_renderer());
	}
	
	SDL_DestroyWindow(game.get_window());
	SDL_Quit();

	return 0;
}
