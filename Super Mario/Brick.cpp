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
	mBouncingStartY = position.y;
	mItemInside = new PowerUp();

	if (brickType == BrickType::QUESTIONBLOCK)
	{
		mIdleAnimation = new Animation(mRenderer, mTexture, mSourceRect, 2 , 2500, RENDERSCALE);
	}
	Texture2D* texture = new Texture2D(mRenderer);
	texture->LoadFromFile("Images/BrickCoin.png");
	mCoinReleased = new Animation(mRenderer, texture, new SDL_Rect{ 0, 0, 32, 48 }, 35, 30, RENDERSCALE);
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
	mBouncingStartY = position.y;
	mItemInside = itemInside;

	if (brickType == BrickType::QUESTIONBLOCK)
	{
		mIdleAnimation = new Animation(mRenderer, mTexture, mSourceRect, 2, 5000, RENDERSCALE);
	}
	if (itemInside == NULL)
	{
		mCoinsInside = true;
	}
	else
	{
		mItemInside = itemInside;
	}
	Texture2D* texture = new Texture2D(mRenderer);
	texture->LoadFromFile("Images/BrickCoin.png");
	mCoinReleased = new Animation(mRenderer, texture, new SDL_Rect{ 0, 0, 32, 48 }, 35, 30, RENDERSCALE);
}

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, BrickType brickType, int coinsInside) : Entity(renderer, imagePath, position, 16, 16)
{
	mSourceRect = new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
	mBeenHit = false;
	mSideHit = NONE;
	mBrickType = brickType;
	mDestroyFallForce = 300;
	mDestroySeperation = 0;
	mDestroyAngle = 0;
	mBouncingStartY = position.y;
	
	if (brickType == BrickType::QUESTIONBLOCK)
	{
		mIdleAnimation = new Animation(mRenderer, mTexture, mSourceRect, 2, 2500, RENDERSCALE);
	}
	Texture2D* texture = new Texture2D(mRenderer);
	texture->LoadFromFile("Images/BrickCoin.png");
	mCoinReleased = new Animation(mRenderer, texture, new SDL_Rect{ 0, 0, 32, 48 }, 46, 20, RENDERSCALE);
	 
	mNumCoinsInside = coinsInside;
	if (coinsInside > 0)
	{
		mCoinsInside = true;
	}
}

Brick::~Brick()
{
	delete mSourceRect;
	delete mItemInside;
	delete mIdleAnimation;
	delete mCoinReleased;
}

void Brick::Update(float deltaTime, SDL_Event e, std::vector<Player*>& players, int & score, int & coinsCollected, int level)
{
	if (level == 2)
	{
		SDL_SetTextureColorMod(mTexture->GetTexture(), 38, 217, 201);
	}

	if (mCoinReleased->Completed() && mCoinsInside)
	{
		score += 100;
		coinsCollected++;
		mCoinsInside = false;
	}

	if (!mDestroyed)
	{
		if (mItemInsideSpawned)
		{
			mItemInside->Update(deltaTime, e);
			for (int i = 0; i < players.size(); i++)
			{
				ItemCollisions(players[i], score);
			}
		}

		if (mBouncing)
		{
			PerformBrickBounce();
		}

		UpdateHitbox();
	}
	else
	{
		mPosition.y -= mDestroyFallForce * deltaTime;
		mDestroyFallForce -= JUMP_FORCE_DECREMENT * deltaTime;
		mDestroySeperation += 0.01;
		mDestroyAngle += 0.05;
	}
}

void Brick::Render(SDL_Rect* camera)
{
	if (mItemInsideSpawned)
	{
		mItemInside->Render(camera);
	}

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
				if (mCoinsInside)
				{
					if (!mCoinReleased->Completed())
					{
						mCoinReleased->Play(Vector2D(mPosition.x - 16, mPosition.y - 64), SDL_FLIP_NONE, camera);
					}
				}

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
		case BREAKABLEBLOCK:
		{
			if (!mDestroyed)
			{
				mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, camera, 0.0f, mSourceRect);
			}
			else
			{
				mTexture->Render(Vector2D(mPosition.x - mDestroySeperation, mPosition.y - mDestroySeperation), SDL_FLIP_NONE, 1, camera, mDestroyAngle, mSourceRect);
				mTexture->Render(Vector2D((mPosition.x + mHitbox->w / 2) + mDestroySeperation, mPosition.y - mDestroySeperation), SDL_FLIP_NONE, 1, camera, mDestroyAngle, mSourceRect);
				mTexture->Render(Vector2D(mPosition.x - mDestroySeperation, mPosition.y + mHitbox->h / 2), SDL_FLIP_NONE, 1, camera, mDestroyAngle, mSourceRect);
				mTexture->Render(Vector2D((mPosition.x + mHitbox->w / 2) + mDestroySeperation, mPosition.y + mHitbox->h / 2), SDL_FLIP_NONE, 1, camera, mDestroyAngle, mSourceRect);
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

void Brick::ItemCollisions(Player* player, int& score)
{
	if (mItemInsideSpawned)
	{
		if (RectContainsRect(mItemInside->GetHitbox(), player->GetHitbox()))
		{
			

			switch (mItemInside->GetType())
			{
				case PowerUpType::MUSHROOM:
				{
					if (player->GetHealth() == 1)
					{
						player->UpdateHealth(+1);
						score += 100;
					}
					else
					{
						score += 200;
					}
					break;
				}

				case PowerUpType::FIREFLOWER:
				{
					if (player->GetHealth() == 1)
					{
						score += 150;
						player->UpdateHealth(+2);
					}
					else if (player->GetHealth() == 2)
					{
						score += 150;
						player->UpdateHealth(+1);
					}
					else
					{
						score += 300;
					}
					break;
				}
			}
			
			delete mItemInside;
			mItemInsideSpawned = false;
		}
	}
}

void Brick::PerformBrickBounce()
{
	if (mBouncingStartY - 10 > mPosition.y)
	{
		mBouncingUp = false;
	}
	if (mBouncingUp)
	{
		mPosition.y -= 0.1;
	}
	else
	{
		if (mPosition.y == mBouncingStartY)
		{
			mBouncing = false;
		}
		mPosition.y += 0.1;
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
				if (!mCoinsInside)
				{
					if (playerHealth == 1)
					{
						mItemInside = new Mushroom(mRenderer, "Images/RedMushroom.png", Vector2D(mPosition.x, mPosition.y), RENDERSCALE, FACING_RIGHT);
					}
					if (playerHealth >= 2)
					{
						mItemInside = new FireFlower(mRenderer, "Images/FireFlower.png", Vector2D(mPosition.x, mPosition.y), RENDERSCALE);
					}

					mItemInsideSpawned = true;
				}
				
				if (!mBeenHit)
				{
					mBouncing = true;
					mBouncingUp = true;
				}

				mSourceRect->y = 16;
				mSourceRect->x = 0;
				mBeenHit = true;
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
				else
				{
					
					mBouncing = true;
					mBouncingUp = true;
				}
				break;
			}

			case COINBLOCK:
			{

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

void Brick::Debug(SDL_Rect* camera, int type)
{
	SDL_Rect* mDebugHitbox = new SDL_Rect{ mHitbox->x - camera->x, mHitbox->y, mHitbox->w, mHitbox->h };

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(mRenderer, mDebugHitbox);

	if (type == 2)
	{
		SDL_Rect* mDebugHitboxLeft = new SDL_Rect{ mSensorLeft->x - camera->x, mSensorLeft->y, mSensorLeft->w, mSensorLeft->h };
		SDL_Rect* mDebugHitboxRight = new SDL_Rect{ mSensorRight->x - camera->x, mSensorRight->y, mSensorRight->w, mSensorRight->h };
		SDL_Rect* mDebugHitboxTop = new SDL_Rect{ mSensorTop->x - camera->x, mSensorTop->y, mSensorTop->w, mSensorTop->h };
		SDL_Rect* mDebugHitboxBottom = new SDL_Rect{ mSensorBottom->x - camera->x, mSensorBottom->y, mSensorBottom->w, mSensorBottom->h };

		SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(mRenderer, mDebugHitboxLeft);
		SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(mRenderer, mDebugHitboxRight);
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
		SDL_RenderDrawRect(mRenderer, mDebugHitboxTop);
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
		SDL_RenderDrawRect(mRenderer, mDebugHitboxBottom);

		delete mDebugHitboxLeft;
		delete mDebugHitboxRight;
		delete mDebugHitboxTop;
		delete mDebugHitboxBottom;
	}

	delete mDebugHitbox;

	if (mItemInsideSpawned)
	{
		mItemInside->Debug(camera, type);
	}
}


