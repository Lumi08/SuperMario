#include "FireFlower.h"

FireFlower::FireFlower(SDL_Renderer* renderer, std::string imagePath, Vector2D spawnLocation, float renderScale) 
	: PowerUp(renderer, imagePath, spawnLocation, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT, FIREFLOWER)
{
	mIdleAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 7500, renderScale);
	SetSpawning(true);
	mStartY = spawnLocation.y;
}

FireFlower::~FireFlower()
{
	delete mIdleAnimation;
}

void FireFlower::Render(SDL_Rect* camera)
{
	mIdleAnimation->Play(mPosition, SDL_FLIP_NONE, camera);
}

void FireFlower::Update(float deltaTime, SDL_Event e)
{
	if (GetSpawning())
	{
		if (mPosition.y >= mStartY - 16 * RENDERSCALE + 1)
		{
			mPosition.y -= 0.025;
		}
		else
		{
			SetSpawning(false);
		}
	}
	UpdateHitbox();
}
