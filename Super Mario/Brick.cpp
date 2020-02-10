#include "Brick.h"
#include "Texture2D.h"

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position) : Entity(renderer, imagePath, position, 16, 16)
{
	mSourceRect = new SDL_Rect{ 0, 0, 16, 16 };
}

Brick::~Brick()
{
	delete mSourceRect;
}

void Brick::Update(float deltaTime, SDL_Event e, Player* players[])
{
	for (int i = 0; i < 2; i++)
	{
		PlayerCollisions(players[i], i);
	}

	if (mItemInsideSpawned)
	{
		mItemInside->Update(deltaTime, e);
		ItemCollisions();
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

void Brick::PlayerCollisions(Player* player, int playerNum)
{
	//ItemCollisions
	if(mItemInsideSpawned)
	{ 
		if (RectIntersects(mItemInside->GetHitbox(), player->GetHitbox()))
		{
			delete mItemInside;
			mItemInsideSpawned = false;
		}
	}

	if (RectIntersects(mHitbox, player->GetHitbox(), mSidePlayerHit[playerNum]))
	{
		if (mSidePlayerHit[playerNum] == SIDE::TOP)
		{
			player->SetY(mPosition.y - player->GetHeight());
			player->SetOnPlatform(true);
		}
		if (mSidePlayerHit[playerNum] == SIDE::BOTTOM)
		{
			player->SetY(mPosition.y + (mRawHeight * RENDERSCALE));
			player->SetOnPlatform(false);
			player->SetJumpForce(0);
			mItemInside = new Mushroom(mRenderer, "Images/RedMushroom.png", Vector2D(mPosition.x, mPosition.y), 2, FACING_RIGHT);
			mItemInsideSpawned = true;
		}
		if (mSidePlayerHit[playerNum] == SIDE::LEFT)
		{
			player->SetX(mPosition.x - (mRawWidth * RENDERSCALE));
			player->SetOnPlatform(false);
		}
		if (mSidePlayerHit[playerNum] == SIDE::RIGHT)
		{
			player->SetX(mPosition.x + player->GetWidth());
			player->SetOnPlatform(false);
		}
	}
	if (player->GetX() > mPosition.x + (mRawHeight * RENDERSCALE) ||
		player->GetX() + player->GetWidth() < mPosition.x)
	{
		player->SetOnPlatform(false);
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
	if (mItemInsideSpawned)
	{
		SDL_RenderDrawRect(mRenderer, mItemInside->GetHitbox());
	}
}


