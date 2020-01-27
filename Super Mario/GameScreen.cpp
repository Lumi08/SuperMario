#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	this->mRenderer = renderer;
}

GameScreen::~GameScreen()
{
	this->mRenderer = NULL;
}

void GameScreen::Render()
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}
