#include "Brick.h"
#include "Texture2D.h"

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, BrickType brickType) : Entity(renderer, imagePath, position, 16, 16)
{
	mSourceRect = new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
	mBeenHit = false;
	mSideHit = NONE;
	mBrickType = brickType;

	if (brickType == BrickType::QUESTIONBLOCK)
	{
		mIdleAnimation = new Animation(mRenderer, mTexture, mSourceRect, 2 ,5000, RENDERSCALE);
	}
}

Brick::~Brick()
{
	delete mSourceRect;
}

void Brick::Update(float deltaTime, SDL_Event e, Player* players[], int playerCount)
{
	for (int i = 0; i < 1; i++)
	{
		//PlayerCollisions(players[i], i, deltaTime);
	}

	if (mItemInsideSpawned)
	{
		mItemInside->Update(deltaTime, e);
		for (int i = 0; i < playerCount; i++)
		{
			ItemCollisions(players[i]);
		}
	}
	//PlayerCollisions(players[0]);
}

void Brick::Render()
{
	if (mItemInsideSpawned)
	{
		mItemInside->Render();
	}
	switch (mBrickType)
	{
		case QUESTIONBLOCK:
		{
			if (!mBeenHit)
			{
				mIdleAnimation->Play(mPosition, SDL_FLIP_NONE);
			}
			else
			{
				mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, 0.0f, mSourceRect);
			}
			break;
		}
		default:
		{

			mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, 0.0f, mSourceRect);
			break;
		}
	}
}

void Brick::Debug(int type)
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
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(mRenderer, mItemInside->GetHitbox());
	}
} 

void Brick::ItemCollisions(Player* player)
{
	if (mItemInsideSpawned)
	{
		if (RectIntersects(mItemInside->GetHitbox(), player->GetHitbox()))
		{
			player->UpdateHealth(1);
			delete mItemInside;
			std::cerr << "test" << std::endl;
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
				if (playerHealth == 2)
				{
					mItemInside = new FireFlower(mRenderer, "Images/RedMushroom.png", Vector2D(mPosition.x, mPosition.y + mHitbox->h), RENDERSCALE);
				}
				mSourceRect->y = 16;
				mSourceRect->x = 0;
				mBeenHit = true;
				mItemInsideSpawned = true;
				break;
			}

			case SECRETBLOCK:
			{
				if (playerHealth == 1)
				{
					mItemInside = new Mushroom(mRenderer, "Images/RedMushroom.png", Vector2D(mPosition.x, mPosition.y), RENDERSCALE, FACING_RIGHT);
				}
				if (playerHealth == 2)
				{
					mItemInside = new FireFlower(mRenderer, "Images/RedMushroom.png", Vector2D(mPosition.x, mPosition.y + mHitbox->h), RENDERSCALE);
				}
				mSourceRect->x = 16;
				mBeenHit = true;
				mItemInsideSpawned = true;
				break;
			}
		}
	}
}


