#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, std::string imgPath, Vector2D spawnLocation) : Entity(renderer, imgPath, spawnLocation, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT)
{
	mSourceRect = new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
	mWalkAnimation = new Animation(mRenderer, mTexture, mSourceRect, 2, 400, RENDERSCALE);
	mFacing = FACING_LEFT;
	mMovementSpeed = 0.10;
	mAlive = true;
}

Enemy::~Enemy()
{

}

void Enemy::Render(SDL_Rect* camera)
{
	if (mAlive)
	{
		mWalkAnimation->Play(mPosition, SDL_FLIP_NONE, camera);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, 0.0f, mSourceRect);
	}
}

void Enemy::Update(float deltaTime, SDL_Event e)
{
	if (mAlive)
	{
		switch (mFacing)
		{
			case FACING_LEFT: 
			{
				mPosition.x -= mMovementSpeed;
				break;
			}

			case FACING_RIGHT:
			{
				mPosition.x += mMovementSpeed;
				break;
			}
		}
		UpdateHitbox();
	}
}

void Enemy::Killed()
{
	mSourceRect->x = 0;
	mSourceRect->y = 16;
	mAlive = false;
}