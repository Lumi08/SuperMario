#include "Mushroom.h"

Mushroom::Mushroom(SDL_Renderer* renderer, std::string imagePath, Vector2D spawnLocation, float renderScale, FACING startDirection) : Entity(renderer, imagePath, spawnLocation, 16, 16)
{
	mSourceRect = new SDL_Rect{ 0, 0, 16, 16 };
	mDirectionFacing = startDirection;
	mMovingAnimation = new Animation(renderer, mTexture, mSourceRect, 2, 10000, renderScale);
	mSpawning = true;
	mOnPlatform = true;
	mStartY = spawnLocation.y;
}

Mushroom::~Mushroom()
{
	delete mSourceRect;
	delete mMovingAnimation;
}

void Mushroom::Render()
{
	mMovingAnimation->Play(mPosition, SDL_FLIP_NONE);
}

void Mushroom::Update(float deltaTime, SDL_Event e)
{
	if (mSpawning)
	{
		if (mPosition.y >= mStartY - 16 * RENDERSCALE - 1)
		{
			mPosition.y -= 0.025;
		}
		else
		{
			mSpawning = false;
		}
	}
	else
	{
		if (mPosition.y < SCREEN_HEIGHT - mRawHeight * RENDERSCALE && !mOnPlatform)
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
