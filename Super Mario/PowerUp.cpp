#include "PowerUp.h"

PowerUp::PowerUp(SDL_Renderer* renderer, std::string imgPath, Vector2D spawnLocation, int width, int height, PowerUpType type) : Entity(renderer, imgPath, spawnLocation, width, height)
{
	mType = type;
}

PowerUp::~PowerUp()
{

}

void PowerUp::Render(SDL_Rect* camera)
{
}

void PowerUp::Update(float deltaTime, SDL_Event e)
{
	
}