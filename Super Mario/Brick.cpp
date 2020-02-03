#include "Entity.h"
#include "Player.h"
#include "Brick.h"
#include "Texture2D.h"

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, float renderScale) : Entity(renderer, imagePath, position, 16, 15, renderScale)
{
	mSourceRect = new SDL_Rect{ 0, 0, 16, 15 };
}

Brick::~Brick()
{
}

void Brick::Update(float deltaTime, SDL_Event e)
{
	
}

void Brick::Render()
{
	mTexture->Render(mPosition, SDL_FLIP_NONE, mRenderScale, 0.0f, mSourceRect);
}


