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
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE, 0, mCamera);
	for (int i = 0; i < mPlayerCount; i++)
	{
		mPlayers[i]->Render(mCamera);
	}
	for (int i = 0; i < mBricks.size(); i++)
	{
		mBricks[i]->Render(mCamera);
	}
	
	if (debug)
	{
		for (int i = 0; i < mPlayerCount; i++)
		{
			mPlayers[i]->Debug(mCamera);
		}
		for (int i = 0; i < mBricks.size(); i++)
		{
			mBricks[i]->Debug(mCamera);
		}
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mCamera->x = mPlayers[0]->GetX() - (SCREEN_WIDTH / 2);
	mCamera->y = mPlayers[0]->GetY() - (SCREEN_WIDTH / 2);

	if (mCamera->x < 0)
	{
		mCamera->x = 0;
	}
	if (mCamera->y < 0)
	{
		mCamera->y = 0;
	}
	if (mCamera->x > mCamera->w)
	{
		mCamera->x = mCamera->w;
	}
	if (mCamera->y < mCamera->h)
	{
		mCamera->y = mCamera->h;
	}

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

	mBrickCount = mBricks.size();

	mPlayers[0] = new Player(mRenderer, "Images/Mario.png", Vector2D(4, 4), 1);
	mPlayers[1] = new Player(mRenderer, "Images/Luigi.png", Vector2D(64, 250), 2);
	mPlayers[0]->UpdateHealth(1);
	map->LoadMapAssets(mPlayers, mBricks);
	//SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	mCamera = new SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

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
				switch (mBricks[j]->GetBrickType())
				{
					case BrickType::SECRETBLOCK:
					{
						mPlayers[i]->SetSideHit(mPlayers[i]->GetSideCollidingWithEntity(mBricks[j]));
						switch (mPlayers[i]->GetSideHit())
						{
							case SIDE::TOP:
							{
								if (mPlayers[i]->GetJumpForce() > 0)
								{
									mPlayers[i]->SetY(mBricks[j]->GetY() + (mBricks[j]->GetHitbox()->h));
									mPlayers[i]->SetJumpForce(0);
									mBricks[j]->Hit(mPlayers[i]->GetHealth());
									mBricks[j]->SetBrickType(BrickType::SOLIDBLOCK);
								}
								break;
							}
						}
						break;
					}

					default:
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
							//if(mPlayers[i].GetJumpf)
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
