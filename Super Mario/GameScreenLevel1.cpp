#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <SDL_ttf.h>


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
	mBackgroundTexture->Render(mBackgroundPosition, SDL_FLIP_NONE, 0, mCamera);
	//mScoreText->Render("Score", Vector2D(10, 10), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);

	mScoreText->Render(Vector2D(10, 10), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);

	for (int i = 0; i < mPlayerCount; i++)
	{
		mPlayers[i]->Render(mCamera);
	}
	for (int i = 0; i < mBricks.size(); i++)
	{
		mBricks[i]->Render(mCamera);	
	}
	for (int i = 0; i < mPipes.size(); i++)
	{
		mPipes[i]->Render(mCamera);
	}
	
	if (debug)
	{
		for (int i = 0; i < mPlayerCount; i++)
		{
			mPlayers[i]->Debug(mCamera, mDebugType);
		}
		for (int i = 0; i < mBricks.size(); i++)
		{
			mBricks[i]->Debug(mCamera, mDebugType);
		}
		for (int i = 0; i < mPipes.size(); i++)
		{
			mPipes[i]->Debug(mCamera, mDebugType);
		}
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	std::cerr << mScore << std::endl;
	
	mScoreText->CreateTextureFromText("Score: " + std::to_string(mScore));

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
	if (mCamera->x > MAPWIDTHPIXELS)
	{
		mCamera->x = MAPWIDTHPIXELS;
	}
	if (mCamera->y < mCamera->h)
	{
		mCamera->y = mCamera->h;
	}

	if (mCamera->x % 1024 == 0)
	{
		mBackgroundPosition.x = mCamera->x - 1024;
	}

	for (int i = 0; i < mPlayerCount; i++)
	{
		mPlayers[i]->Update(deltaTime, e);
		bool playerBotCollided = false;
		BrickCollisionsWithPlayer(mPlayers[i], playerBotCollided);
		PipeCollisionsWithPlayer(mPlayers[i], playerBotCollided);

		if (!playerBotCollided)
		{
			mPlayers[i]->SetOnPlatform(false);
			mPlayers[i]->SetJumping(true);
		}
	}
	for (int i = 0; i < mBricks.size(); i++)
	{
		
		mBricks[i]->Update(deltaTime, e, mPlayers, mPlayerCount, mScore);

		if (mBricks[i]->GetItemInsideSpawned())
		{
			SpawnedItemSolidBlockCollisions(mBricks[i]->GetItemInside());
		}
		if (mBricks[i]->GetDestroyed())
		{
			RemoveDestroyedBricks(mBricks[i], i);
		}
		
	}
	for (int i = 0; i < mPipes.size(); i++)
	{
		mPipes[i]->Update(deltaTime, e);
	}


	
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
	mCamera = new SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	
	mScoreText = new Text(mRenderer, "Font/OpenSans-Regular.ttf", SDL_Color{ 255, 0, 0, 255 }, 20);
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/unnamed.png"))
	{
		std::cout << "Error: Failed to load background texture!" << std::endl;
		return false;
	}
	
	mScore = 0;
	mScoreText = new Text(mRenderer, "Font/OpenSans-Regular.ttf", SDL_Color{ 255 , 0, 0, 255 }, 20);

	mBackgroundPosition = Vector2D(0, 0);
	mPlayerCount = 2;
	MapLoader* map = new MapLoader((char*)"map1.txt", mRenderer);

	mPlayers[0] = new Player(mRenderer, "Images/Mario.png", Vector2D(4, 4), 1);
	mPlayers[1] = new Player(mRenderer, "Images/Luigi.png", Vector2D(64, 250), 2);
	//mPlayers[0]->UpdateHealth(1);
	map->LoadMapAssets(mPlayers, mBricks, mPipes);
	//SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	return true;
}

//Use the players bottom sensor to detect wether it is on a platform or not
void GameScreenLevel1::BrickCollisionsWithPlayer(Player* player, bool& botCollided)
{
	for (int j = 0; j < mBricks.size(); j++)
	{
		if (player->IsCollidingWith(mBricks[j]))
		{
			switch (mBricks[j]->GetBrickType())
			{
			case BrickType::SECRETBLOCK:
			{
				//player->SetSideHit(player->GetSideCollidingWithEntity(mBricks[j]));
				switch (player->GetSideCollidingWithEntity(mBricks[j]))
				{
					case SIDE::TOP:
					{
						if (player->GetJumpForce() > 0)
						{
							player->SetY(mBricks[j]->GetY() + (mBricks[j]->GetHitbox()->h));
							player->SetJumpForce(0);
							mBricks[j]->Hit(player->GetHealth());
							mBricks[j]->SetBrickType(BrickType::SOLIDBLOCK);
						}
						break;
					}
				}
				break;
			}

			default:
			{
				player->SetSideHit(player->GetSideCollidingWithEntity(mBricks[j]));
				switch (player->GetSideHit())
				{
					case SIDE::BOTTOM:
					{
						player->SetY(mBricks[j]->GetY() - player->GetHitbox()->h);
						player->SetOnPlatform(true);
						break;
					}
					case SIDE::TOP:
					{
						//if(mPlayers[i].GetJumpf)
						player->SetY(mBricks[j]->GetY() + (mBricks[j]->GetHitbox()->h));
						player->SetJumpForce(0);
						mBricks[j]->Hit(player->GetHealth());
						break;
					}
					case SIDE::RIGHT:
					{
						player->SetX(mBricks[j]->GetX() - (player->GetHitbox()->w));
						break;
					}
					case SIDE::LEFT:
					{
						player->SetX(mBricks[j]->GetX() + player->GetHitbox()->w);
						break;
					}
				}
				break;
			}
			}
		}

		if (RectIntersects(player->GetBottomSensorBox(), mBricks[j]->GetHitbox()))
		{
			if (mBricks[j]->GetBrickType() != BrickType::SECRETBLOCK)
			{
				botCollided = true;
			}
		}
		
	}
}

void GameScreenLevel1::PipeCollisionsWithPlayer(Player* player, bool& botCollided)
{
	for (int j = 0; j < mPipes.size(); j++)
	{
		if (player->IsCollidingWith(mPipes[j]))
		{
			//player->SetSideHit(player->GetSideCollidingWithEntity(mPipes[j]));
			switch (player->GetSideCollidingWithEntity(mPipes[j]))
			{
				case SIDE::BOTTOM:
				{
					player->SetY(mPipes[j]->GetY() - player->GetHitbox()->h);
					player->SetOnPlatform(true);
					break;
				}
				case SIDE::RIGHT:
				{
					player->SetX(mPipes[j]->GetX() - (player->GetHitbox()->w));
					break;
				}
				case SIDE::LEFT:
				{
					player->SetX(mPipes[j]->GetX() + player->GetHitbox()->w);
					break;
				}
			}
		}
		if (RectIntersects(player->GetBottomSensorBox(), mPipes[j]->GetHitbox()))
		{
			botCollided = true;
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

void GameScreenLevel1::SpawnedItemSolidBlockCollisions(PowerUp* powerup)
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

	for (int j = 0; j < mPipes.size(); j++)
	{
		if (powerup->IsCollidingWith(mPipes[j]))
		{
			//player->SetSideHit(player->GetSideCollidingWithEntity(mPipes[j]));
			switch (powerup->GetSideCollidingWithEntity(mPipes[j]))
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
		if (RectIntersects(powerup->GetBottomSensorBox(), mPipes[j]->GetHitbox()))
		{
			botCollided = true;
		}
	}
	
	if (!botCollided)
	{
		powerup->SetOnPlatform(false);
	}
}