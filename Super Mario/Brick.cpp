#include "Brick.h"
#include "Texture2D.h"

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position) : Entity(renderer, imagePath, position, 16, 16)
{
	mSourceRect = new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
	mBeenHit = false;
	mPreviousSideHit = NONE;
}

Brick::~Brick()
{
	delete mSourceRect;
}

void Brick::Update(float deltaTime, SDL_Event e, Player* players[])
{
	for (int i = 0; i < 1; i++)
	{
		//PlayerCollisions(players[i], i, deltaTime);
	}

	if (mItemInsideSpawned)
	{
		mItemInside->Update(deltaTime, e);
		//ItemCollisions();
	}
	//PlayerCollisions(players[0]);
}

void Brick::Render()
{
	if (mItemInsideSpawned)
	{
		mItemInside->Render();
	}
	mTexture->Render(mPosition, SDL_FLIP_NONE, RENDERSCALE, 0.0f, mSourceRect);
}

void Brick::PlayerCollisions(Player* player, int playerNum, float deltaTime)
{
	//ItemCollisions
	if(mItemInsideSpawned)
	{ 
		if (RectIntersects(mItemInside->GetHitbox(), player->GetHitbox()))
		{
			if (player->GetHealth() < 2)
			{
				player->UpdateHealth(+1);
			}
			delete mItemInside;
			mItemInsideSpawned = false;
		}
	}
	

	if (RectIntersects(mHitbox, player->GetHitbox()))
	{
		SIDE sideHit = RectGetSideHit(mHitbox, player->GetHitbox(), deltaTime, mRenderer);
		switch (sideHit)
		{
			case SIDE::TOP:
			{
				if (sideHit != mPreviousSideHit)
				{
					player->SetY(mPosition.y - player->GetHitbox()->h);
					player->SetOnPlatform(true);
				}
				break;
			}
			case SIDE::BOTTOM:
			{
				if (sideHit != mPreviousSideHit)
				{
				player->SetY(mPosition.y + (mHitbox->h));
				player->SetOnPlatform(false);
				player->SetJumpForce(0);
				if (!mBeenHit)
				{
					if (player->GetHealth() == 1)
					{
						mItemInside = new Mushroom(mRenderer, "Images/RedMushroom.png", Vector2D(mPosition.x, mPosition.y), 2, FACING_RIGHT);
					}
					if (player->GetHealth() == 2)
					{
						mItemInside = new FireFlower(mRenderer, "Images/FireFlower.png", Vector2D(mPosition.x, mPosition.y), 2);
					}
					mItemInsideSpawned = true;
					mSourceRect->x = DEFAULTTILEHEIGHT;
				}
				mBeenHit = true;
				}
				break;
			}
			case SIDE::LEFT:
			{
				player->SetX(mPosition.x - (player->GetHitbox()->w));
				player->SetOnPlatform(false);
				break;
			}
			case SIDE::RIGHT:
			{
				player->SetX(mPosition.x + player->GetWidth());
				player->SetOnPlatform(false);
				break;
			}
		}
		mPreviousSideHit = sideHit;
	}
}

void Brick::ItemCollisions()
{
	if (mItemInside->GetOnPlatform() != false)
	{
		if (mItemInside->GetX() > mPosition.x + (mRawHeight * RENDERSCALE) ||
			mItemInside->GetX() + mItemInside->GetWidth() < mPosition.x)
		{
			mItemInside->SetOnPlatform(false);
		}
	}
}

void Brick::Debug()
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
		SDL_RenderDrawRect(mRenderer, mItemInside->GetHitbox());
	}
}


