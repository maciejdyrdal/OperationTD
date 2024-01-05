#include "GameState.h"

GameState::GameState(SDL_Window* window, SDL_Renderer* renderer)
	:m_Window{window}, m_Renderer{renderer} {}

GameState::~GameState()
{
	//Destroy window
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Window = NULL;
	m_Renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
