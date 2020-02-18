#include "Brick.h"
#include "Texture2D.h"

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position) : Entity(renderer, imagePath, position, 16, 16)
{
	mSourceRect = new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT };
	mBeenHit = false;
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
			player->UpdateHealth(+1);
			delete mItemInside;
			mItemInsideSpawned = false;
		}
	}
	//std::cout << mSidePlayerHit[0] << std::endl;
	if (RectIntersects(mHitbox, player->GetHitbox(), mSidePlayerHit[playerNum]))
	{
		
		if(mSidePlayerHit[playerNum] == TOP)
		{
			player->SetY(mPosition.y - player->GetHitbox()->h);
			player->SetOnPlatform(true);
		}

		if (mSidePlayerHit[playerNum] == BOTTOM)
		{
			player->SetY(mPosition.y + (mHitbox->h));
			player->SetOnPlatform(false);
			player->SetJumpForce(0);
			if (!mBeenHit)
			{
				mItemInside = new Mushroom(mRenderer, "Images/RedMushroom.png", Vector2D(mPosition.x, mPosition.y), 2, FACING_RIGHT);
				mItemInsideSpawned = true;
				mSourceRect->x = DEFAULTTILEHEIGHT;
			}
			mBeenHit = true;
		}
		if (mSidePlayerHit[playerNum] == LEFT)
		{
			player->SetX(mPosition.x - (player->GetHitbox()->w));
			player->SetOnPlatform(false);
		}
		if (mSidePlayerHit[playerNum] == RIGHT)
		{
			player->SetX(mPosition.x + player->GetWidth());
			player->SetOnPlatform(false);
		}
		
	}
	if (player->GetX() > mPosition.x + (player->GetHitbox()->w) ||
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
	SDL_RenderDrawRect(mRenderer, mHitbox);
	if (mItemInsideSpawned)
	{
		SDL_RenderDrawRect(mRenderer, mItemInside->GetHitbox());
	}
}


