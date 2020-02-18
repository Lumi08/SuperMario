#include "Mushroom.h"

Mushroom::Mushroom(SDL_Renderer* renderer, std::string imagePath, Vector2D spawnLocation, float renderScale, FACING startDirection) : PowerUp(renderer, imagePath, spawnLocation, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT)
{
	mDirectionFacing = startDirection;
	mMovingAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 10000, renderScale);
	SetSpawning(true);
	SetOnPlatform(true);
	mStartY = spawnLocation.y;
}

Mushroom::~Mushroom()
{
	delete mMovingAnimation;
}

void Mushroom::Render()
{
	mMovingAnimation->Play(mPosition, SDL_FLIP_NONE);
}

void Mushroom::Update(float deltaTime, SDL_Event e)
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
	else
	{
		if (mPosition.y < SCREEN_HEIGHT - mRawHeight * RENDERSCALE && !GetOnPlatform())
		{
			mPosition.y += GRAVITY * deltaTime;
		}

		if (mDirectionFacing == FACING_RIGHT)
		{
			mPosition.x += 0.03;
		}

		if (mDirectionFacing == FACING_LEFT)
		{
			mPosition.x -= 0.03;
		}
	}

	UpdateHitbox();
}
