#include "Brick.h"
#include "Texture2D.h"

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, BrickType brickType) : Entity(renderer, imagePath, position, 16, 16)
{
	mSourceRect = new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
	mBeenHit = false;
	mSideHit = NONE;
	mBrickType = brickType;
	mDestroyFallForce = 300;
	mDestroySeperation = 0;
	mDestroyAngle = 0;
	if (brickType == BrickType::QUESTIONBLOCK)
	{
		mIdleAnimation = new Animation(mRenderer, mTexture, mSourceRect, 2 ,5000, RENDERSCALE);
	}
}

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, BrickType brickType, PowerUp* itemInside) : Entity(renderer, imagePath, position, 16, 16)
{
	mSourceRect = new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
	mBeenHit = false;
	mSideHit = NONE;
	mBrickType = brickType;
	mDestroyFallForce = 300;
	mDestroySeperation = 0;
	mDestroyAngle = 0;
	if (brickType == BrickType::QUESTIONBLOCK)
	{
		mIdleAnimation = new Animation(mRenderer, mTexture, mSourceRect, 2, 5000, RENDERSCALE);
	}
	mItemInside = itemInside;
}

Brick::~Brick()
{
	delete mSourceRect;
}

void Brick::Update(float deltaTime, SDL_Event e, Player* players[], int playerCount)
{
	if (!mDestroyed)
	{
		if (mItemInsideSpawned)
		{
			mItemInside->Update(deltaTime, e);
			for (int i = 0; i < playerCount; i++)
			{
				ItemCollisions(players[i]);
			}
		}
		UpdateHitbox();
	}
	else
	{
		mPosition.y -= mDestroyFallForce * deltaTime;
		mDestroyFallForce -= JUMP_FORCE_DECREMENT * deltaTime;
		mDestroySeperation += 0.01;
		mDestroyAngle += 0.025;
	}
}

void Brick::Render(SDL_Rect* camera)
{
	if (mItemInsideSpawned)
	{
		mItemInside->Render(camera);
	}
	if (!mDestroyed)
	{
		switch (mBrickType)
		{
			case QUESTIONBLOCK:
			{
				if (!mBeenHit)
				{
					mIdleAnimation->Play(mPosition, SDL_FLIP_NONE, camera);
				}
				else
				{
					mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, camera, 0.0f, mSourceRect);
				}
				break;
			}
			case SECRETBLOCK:
			{
				if (mBeenHit)
				{
					mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, camera, 0.0f, mSourceRect);
				}
				break;
			}
			default:
			{

				mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, camera, 0.0f, mSourceRect);
				break;
			}
		}
	}
	else 
	{
		mTexture->Render(Vector2D(mPosition.x - mDestroySeperation, mPosition.y - mDestroySeperation), SDL_FLIP_NONE, 1, camera, mDestroyAngle, mSourceRect);
		mTexture->Render(Vector2D((mPosition.x + mHitbox->w / 2) + mDestroySeperation, mPosition.y - mDestroySeperation), SDL_FLIP_NONE, 1, camera, mDestroyAngle, mSourceRect);
		mTexture->Render(Vector2D(mPosition.x - mDestroySeperation, mPosition.y + mHitbox->h / 2), SDL_FLIP_NONE, 1, camera, mDestroyAngle, mSourceRect);
		mTexture->Render(Vector2D((mPosition.x + mHitbox->w / 2) + mDestroySeperation, mPosition.y + mHitbox->h / 2), SDL_FLIP_NONE, 1, camera, mDestroyAngle, mSourceRect);
	}
}

void Brick::Debug(SDL_Rect* camera)
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(mRenderer, mHitbox);
	
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(mRenderer, mSensorLeft);
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(mRenderer, mSensorRight);
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(mRenderer, mSensorTop);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(mRenderer, mSensorBottom);
	

	if (mItemInsideSpawned)
	{
		mItemInside->Debug(camera);
	}
} 

void Brick::ItemCollisions(Player* player)
{
	if (mItemInsideSpawned)
	{
		if (RectIntersects(mItemInside->GetHitbox(), player->GetHitbox()))
		{
			switch (mItemInside->GetType())
			{
				case PowerUpType::MUSHROOM:
				{
					if (player->GetHealth() == 1)
					{
						player->UpdateHealth(+1);
					}
					else
					{
						//Score goes up
					}
					break;
				}

				case PowerUpType::FIREFLOWER:
				{
					if (player->GetHealth() == 1)
					{
						player->UpdateHealth(+2);
					}
					else if (player->GetHealth() == 2)
					{
						player->UpdateHealth(+1);
					}
					else
					{
						//Score goes up
					}
					break;
				}
			}
			
			
			delete mItemInside;
			//std::cerr << "test" << std::endl;
			mItemInsideSpawned = false;
		}
	}
}

void Brick::Hit(int playerHealth)
{
	if (!mBeenHit)
	{
		switch (mBrickType)
		{
			case QUESTIONBLOCK:
			{
				if (playerHealth == 1)
				{
					mItemInside = new Mushroom(mRenderer, "Images/RedMushroom.png", Vector2D(mPosition.x, mPosition.y), RENDERSCALE, FACING_RIGHT);
				}
				if (playerHealth >= 2)
				{
					mItemInside = new FireFlower(mRenderer, "Images/FireFlower.png", Vector2D(mPosition.x, mPosition.y), RENDERSCALE);
				}
				mSourceRect->y = 16;
				mSourceRect->x = 0;
				mBeenHit = true;
				mItemInsideSpawned = true;
				break;
			}

			case SECRETBLOCK:
			{
				mSourceRect->x = 16;
				mBeenHit = true;
				mItemInsideSpawned = true;
				break;
			}

			case BREAKABLEBLOCK:
			{
				if (playerHealth > 1)
				{
					Destroy();
				}
				break;
			}
		}
	}
}

void Brick::Destroy()
{
	mDestroyed = true;
	mHitbox->x = -1;
	mHitbox->y = -1;
}


