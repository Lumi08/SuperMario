#include "Mushroom.h"

Mushroom::Mushroom(SDL_Renderer* renderer, std::string imagePath, Vector2D spawnLocation, float renderScale, FACING startDirection) : Entity(renderer, imagePath, spawnLocation, 16, 16, renderScale)
{
	mSourceRect = new SDL_Rect{ 0, 0, 16, 16 };
	mDirectionFacing = startDirection;
	mMovingAnimation = new Animation(renderer, mTexture, mSourceRect, 2, 10000, renderScale);
}

Mushroom::~Mushroom()
{

}

void Mushroom::Render()
{
	mMovingAnimation->Play(mPosition, SDL_FLIP_NONE);
}

void Mushroom::Update(float deltaTime, SDL_Event e)
{

}
