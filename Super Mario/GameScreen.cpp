#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	this->mRenderer = renderer;
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;
}

void GameScreen::Render()
{
}

void GameScreen::update(float deltaTime, SDL_Event e)
{
}
