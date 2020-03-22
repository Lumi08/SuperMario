#include "Mushroom.h"

Mushroom::Mushroom(SDL_Renderer* renderer, std::string imagePath, Vector2D spawnLocation, float renderScale, FACING startDirection) 
	: PowerUp(renderer, imagePath, Vector2D(spawnLocation.x, spawnLocation.y -1), DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT, MUSHROOM)
{
	SetDirectionFacing(startDirection);
	mMovingAnimation = new Animation(renderer, mTexture, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 5000, renderScale);
	SetSpawning(true);
	SetOnPlatform(true);
	mStartY = spawnLocation.y;
	mMovementSpeed = 0.125;
}

Mushroom::~Mushroom()
{
	delete mMovingAnimation;
}

void Mushroom::Render(SDL_Rect* camera)
{
	mMovingAnimation->Play(mPosition, SDL_FLIP_NONE, camera);
}

void Mushroom::Update(float deltaTime, SDL_Event e)
{
	if (GetSpawning())
	{
		if (mPosition.y >= mStartY - 16 * RENDERSCALE + 1)
		{
			mPosition.y -= 0.1;
		}
		else
		{
			SetSpawning(false);
		}
	}
	else
	{
		if (!GetOnPlatform())
		{
			mPosition.y += GRAVITY * deltaTime;
		}

		if (GetDirectionFacing() == FACING_RIGHT)
		{
			mPosition.x += mMovementSpeed;
		}

		if (GetDirectionFacing() == FACING_LEFT)
		{
			mPosition.x -= mMovementSpeed;
		}
		UpdateHitbox();
		UpdateSensors();
	}
}
