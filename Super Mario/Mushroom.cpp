#include "Mushroom.h"

Mushroom::Mushroom(SDL_Renderer* renderer, std::string imagePath, Vector2D spawnLocation, float renderScale, FACING startDirection) 
	: PowerUp(renderer, imagePath, spawnLocation, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT, MUSHROOM)
{
	mDirectionFacing = startDirection;
	mMovingAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 7500, renderScale);
	SetSpawning(true);
	SetOnPlatform(true);
	mStartY = spawnLocation.y;
	mMovementSpeed = 0.03;
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
			mPosition.x += mMovementSpeed;
		}

		if (mDirectionFacing == FACING_LEFT)
		{
			mPosition.x -= mMovementSpeed;
		}
	}

	UpdateHitbox();
}
