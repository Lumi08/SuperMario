#include "GameScreenLevel1.h"
#include "Texture2D.h"


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	mBackgroundTexture = NULL;
}

void GameScreenLevel1::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE, 0);
	for (int i = 0; i < mPlayerCount; i++)
	{
		mPlayers[i]->Render();
	}
	for (int i = 0; i < mBrickCount; i++)
	{
		mBricks[i]->Render();
	}
	
	if (debug)
	{
		for (int i = 0; i < mPlayerCount; i++)
		{
			mPlayers[i]->Debug(debugType);
		}
		for (int i = 0; i < mBrickCount; i++)
		{
			mBricks[i]->Debug(debugType);
		}
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	for (int i = 0; i < mPlayerCount; i++)
	{
		mPlayers[i]->Update(deltaTime, e);
	}
	for (int i = 0; i < mBrickCount; i++)
	{
		mBricks[i]->Update(deltaTime, e, mPlayers);
	}

	BrickCollisionsWithPlayer();

	
	switch (e.type)
	{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_i:
				{
					mPlayers[0]->SetX(100);
					mPlayers[0]->SetY(300);
					break;
				}

				case SDLK_F3:
				{	
					debug = !debug;
					break;
				}

				case SDLK_8:
				{
					for (int j = 0; j < mBrickCount; j++)
					{
						std::cout << "Brick " << j << ": " << mBricks[j]->GetSideHit() << std::endl;
					}
				}

			}
			break;
		}
		case SDL_KEYUP:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_F3:
				{
					f3Down = false;
					break;
				}
			}
			break;
		}
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/bkground.png"))
	{
		std::cout << "Error: Failed to load background texture!" << std::endl;
		return false;
	}
	
	mPlayerCount = 1;
	MapLoader* map = new MapLoader((char*)"map1.txt", mRenderer);
	map->LoadMapAssets(mPlayers, mBricks);

	mBrickCount = map->GetActualBrickCount();

	mPlayers[0] = new Player(mRenderer, "Images/Mario.png", Vector2D(4, 4), 1);
	//mPlayers[1] = new Player(mRenderer, "Images/Luigi.png", Vector2D(64, 250), 2);
	//SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	return true;
	//mCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));
}

void GameScreenLevel1::BrickCollisionsWithPlayer()
{
	for (int i = 0; i < mPlayerCount; i++)
	{
		for (int j = 0; j < mBrickCount; j++)
		{
			if (mBricks[j]->GetSideHit() == SIDE::TOP)
			{
				if (mPlayers[i]->GetX() > mBricks[j]->GetX() + mBricks[j]->GetHitbox()->h ||
					mPlayers[i]->GetX() + mPlayers[i]->GetWidth() < mBricks[j]->GetX())
				{
					mPlayers[i]->SetOnPlatform(false);
					mBricks[j]->SetSideHit(SIDE::NONE);
				}
			}

			if (mBricks[j]->IsCollidingWith(mPlayers[i]))
			{
				mBricks[j]->SetSideHit(mBricks[j]->GetSideCollidingWithEntity(mPlayers[i]));

				switch (mBricks[j]->GetSideHit())
				{
					case SIDE::TOP:
					{
						mPlayers[i]->SetY(mBricks[j]->GetY() - mPlayers[i]->GetHitbox()->h);
						mPlayers[i]->SetOnPlatform(true);

						break;
					}
					case SIDE::BOTTOM:
					{

						mPlayers[i]->SetY(mBricks[j]->GetY() + (mPlayers[i]->GetHitbox()->h));
						//mPlayers[i]->SetOnPlatform(false);
						mPlayers[i]->SetJumpForce(0);

						//DO MUSHROOM LOGIC
						break;
					}
					case SIDE::LEFT:
					{
						mPlayers[i]->SetX(mBricks[j]->GetX() - (mPlayers[i]->GetHitbox()->w));
						//mPlayers[i]->SetOnPlatform(false);

						break;
					}
					case SIDE::RIGHT:
					{
						mPlayers[i]->SetX(mBricks[j]->GetX() + mPlayers[i]->GetHitbox()->w);
						//mPlayers[i]->SetOnPlatform(false);

						break;
					}
				}
			}
		}
	}
}
