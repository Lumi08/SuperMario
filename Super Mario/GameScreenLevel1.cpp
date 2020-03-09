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
	for (int i = 0; i < mBricks.size(); i++)
	{
		mBricks[i]->Render();
	}
	
	if (debug)
	{
		for (int i = 0; i < mPlayerCount; i++)
		{
			mPlayers[i]->Debug(debugType);
		}
		for (int i = 0; i < mBricks.size(); i++)
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
	for (int i = 0; i < mBricks.size(); i++)
	{
		mBricks[i]->Update(deltaTime, e, mPlayers, mPlayerCount);

		if (mBricks[i]->GetItemInsideSpawned())
		{
			BrickCollisionsWithSpawnedItem(mBricks[i]->GetItemInside());
		}
		if (mBricks[i]->GetDestroyed())
		{
			RemoveDestroyedBricks(mBricks[i], i);
		}
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
	
	mPlayerCount = 2;
	MapLoader* map = new MapLoader((char*)"map1.txt", mRenderer);
	map->LoadMapAssets(mPlayers, mBricks);

	mBrickCount = mBricks.size();

	mPlayers[0] = new Player(mRenderer, "Images/Mario.png", Vector2D(4, 4), 1);
	mPlayers[1] = new Player(mRenderer, "Images/Luigi.png", Vector2D(64, 250), 2);
	mPlayers[0]->UpdateHealth(1);
	//SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	return true;
}

//Use the players bottom sensor to detect wether it is on a platform or not
void GameScreenLevel1::BrickCollisionsWithPlayer()
{
	for (int i = 0; i < mPlayerCount; i++)
	{
		bool botCollided = false;
		for (int j = 0; j < mBricks.size(); j++)
		{
			if (mPlayers[i]->IsCollidingWith(mBricks[j]))
			{
				mPlayers[i]->SetSideHit(mPlayers[i]->GetSideCollidingWithEntity(mBricks[j]));
				switch (mPlayers[i]->GetSideHit())
				{
					case SIDE::BOTTOM:
					{
						mPlayers[i]->SetY(mBricks[j]->GetY() - mPlayers[i]->GetHitbox()->h);
						mPlayers[i]->SetOnPlatform(true);
						break;
					}
					case SIDE::TOP:
					{
						mPlayers[i]->SetY(mBricks[j]->GetY() + (mBricks[j]->GetHitbox()->h));
						mPlayers[i]->SetJumpForce(0);
						mBricks[j]->Hit(mPlayers[i]->GetHealth());
						break;
					}
					case SIDE::RIGHT:
					{
						mPlayers[i]->SetX(mBricks[j]->GetX() - (mPlayers[i]->GetHitbox()->w));
						break;
					}
					case SIDE::LEFT:
					{
						mPlayers[i]->SetX(mBricks[j]->GetX() + mPlayers[i]->GetHitbox()->w);
						break;
					}
				}

				switch (mBricks[j]->GetSideCollidingWithEntity(mPlayers[i]))
				{
					case SIDE::BOTTOM:
					{
						if (mBricks[j]->GetBrickType() == BrickType::BREAKABLEBLOCK)
						{
							if (mPlayers[i]->GetHealth() > 1)
							{
								mBricks[j]->Destroy();
							}
						}
						break;
					}
				}
			}

			if (RectIntersects(mPlayers[i]->GetBottomSensorBox(), mBricks[j]->GetHitbox()))
			{
				botCollided = true;
			}

			
		}
		if (!botCollided)
		{
			mPlayers[i]->SetOnPlatform(false);
		}
	}
}

void GameScreenLevel1::RemoveDestroyedBricks(Brick* brick, int brickNum)
{
	if (brick->GetY() > SCREEN_HEIGHT)
	{
		mBricks.erase(mBricks.begin() + brickNum);
	}
}

void GameScreenLevel1::BrickCollisionsWithSpawnedItem(PowerUp* powerup)
{
	bool botCollided = false;
	for (int i = 0; i < mBricks.size(); i++)
	{
		if (powerup->IsCollidingWith(mBricks[i]))
		{
			switch (powerup->GetSideCollidingWithEntity(mBricks[i]))
			{
				case SIDE::BOTTOM:
				{
					powerup->SetOnPlatform(true);
					break;
				}

				case SIDE::RIGHT:
				{
					powerup->SetDirectionFacing(FACING_LEFT);
					break;
				}

				case SIDE::LEFT:
				{
					powerup->SetDirectionFacing(FACING_RIGHT);
					break;
				}
			}
		}

		if (RectIntersects(powerup->GetBottomSensorBox(), mBricks[i]->GetHitbox()))
		{
			botCollided = true;
		}
	}
	
	if (!botCollided)
	{
		powerup->SetOnPlatform(false);
	}
}
