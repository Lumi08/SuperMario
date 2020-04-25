#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <SDL_ttf.h>


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* manager, int numOfPlayers) : GameScreen(renderer)
{
	mManager = manager;
	mCoinsCollected = 0;
	mScore = 0;
	mLives = 3;
	mCurrentLevel = 1;
	mPlayerCount = numOfPlayers;

	mCoinCollectedSound = new SoundEffect("Audio/coin collected.wav");
	mStompSound = new SoundEffect("Audio/stomp.wav");
	mCourseClearSound = new SoundEffect("Audio/course clear.wav");
	mPowerUpCollectedSound = new SoundEffect("Audio/powerup.wav");
	mPowerUpSpawnedSound = new SoundEffect("Audio/powerupspawn.wav");
	mBreakBlockSound = new SoundEffect("Audio/breakblock.wav");
	mBumpBlockSound = new SoundEffect("Audio/bump.wav");
	mCoinCollectedSound = new SoundEffect("Audio/coin collected.wav");

	SetUpLevel(numOfPlayers);
}

bool GameScreenLevel1::SetUpLevel(int numOfPlayers)
{
	mCamera = new SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	std::string bkstring = "Images/unnamed" + std::to_string(mCurrentLevel) + ".png";
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile(bkstring))
	{
		std::cout << "Error: Failed to load background texture!" << std::endl;
		return false;
	}

	if (mCurrentLevel == 1)
	{
		mMusic = new SoundEffect("Audio/Mario.wav");
		mMusic->Play(0);
	}
	if (mCurrentLevel == 2)
	{
		
		mMusic = new SoundEffect("Audio/underground.wav");
		mMusic->Play(0);
	}

	mMarioFace = new Texture2D(mRenderer);
	mMarioFace->LoadFromFile("Images/MarioHead.png");
	mLuigiFace = new Texture2D(mRenderer);
	mLuigiFace->LoadFromFile("Images/LuigiHead.png");

	//mPlayers[1] = new Player(mRenderer, "Images/Luigi.png", Vector2D(64, 250), 2);

	mDeathScreenText = new Text(mRenderer, "Font/SuperMario256.ttf", SDL_Color{ 255, 255, 255, 255 }, 80);
	mScoreText = new Text(mRenderer, "Font/SuperMario256.ttf", SDL_Color{ 255, 255, 255, 255 }, 20);
	mDebugText = new Text(mRenderer, "Font/Oxanium-Regular.ttf", SDL_Color{ 0, 0, 0, 255 }, 20);

	

	mBackgroundPosition = Vector2D(0, 0);
	//mFlag = new Flag(mRenderer, "Images/Flag.png", Vector2D(0, 0));
	std::string level = "Levels/" + std::to_string(mCurrentLevel) + ".txt";
	MapLoader* map = new MapLoader((char*)level.c_str(), mRenderer);
	mMapTileWidth = map->GetTileWidth();
	map->LoadMapAssets(numOfPlayers, mPlayers, mBricks, mPipes, mCoins, mEnemys, mFlag);
	
	if (mCurrentLevel >= 2)
	{
		//mCamera->y = 11 * 32;
		for (int i = 0; i < mPlayers.size(); i++)
		{
			mPlayers[i]->UpdateHealth(mPreviousHealth[i] - 1);
		}

		if (mPlayers.size() == 2)
		{
			mPreviousHealth[0] = 1;
			mPreviousHealth[1] = 1;
		}
		else
		{
			mPreviousHealth[0] = 1;
		}
	}
	
	mResetingLevel = false;
	return true;
}

void GameScreenLevel1::ClearLevel()
{
	delete mMusic;

	mCamera = NULL;
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	
	delete mMarioFace;
	mMarioFace = NULL;

	delete mLuigiFace;
	mLuigiFace = NULL;

	delete mDeathScreenText;
	mDeathScreenText = NULL;

	delete mScoreText;
	mScoreText = NULL;

	delete mDebugText;
	mDebugText = NULL;

	delete mFlag;
	mFlag = NULL;

	mPlayers.clear();
	mBricks.clear();
	mCoins.clear();
	mPipes.clear();
	mEnemys.clear();
}

GameScreenLevel1::~GameScreenLevel1()
{
	
}

void GameScreenLevel1::Render()
{
	if (mResetingLevel)
	{
		//DeathScreen
		mDeathScreenText->SetColor(SDL_Color{ 255, 0, 0, 255 });
		mDeathScreenText->CreateTextureFromText("You Died");
		mDeathScreenText->Render(Vector2D(300, 130), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);
		mDeathScreenText->SetColor(SDL_Color{ 255, 255, 255, 255 });
		mDeathScreenText->CreateTextureFromText("Lives");
		mDeathScreenText->Render(Vector2D(380, 330), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);
		mDeathScreenText->CreateTextureFromText(std::to_string(mLives));
		mDeathScreenText->Render(Vector2D(480, 400), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);
		mMarioFace->Render(Vector2D(200, 405), SDL_FLIP_NONE, 5);
		mLuigiFace->Render(Vector2D(700, 400), SDL_FLIP_NONE, 5);
		return;
	}

	mBackgroundTexture->Render(mBackgroundPosition, SDL_FLIP_NONE, 0, mCamera);
	//mScoreText->Render("Score", Vector2D(10, 10), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);
	
	mScoreText->CreateTextureFromText("Score");
	mScoreText->Render(Vector2D(20, 30), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);
	mScoreText->CreateTextureFromText(std::to_string(mScore));
	mScoreText->Render(Vector2D(20, 50), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);

	mScoreText->CreateTextureFromText("Coins");
	mScoreText->Render(Vector2D(120, 30), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);
	mScoreText->CreateTextureFromText(std::to_string(mCoinsCollected));
	mScoreText->Render(Vector2D(120, 50), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);

	mScoreText->CreateTextureFromText("Lives");
	mScoreText->Render(Vector2D(220, 30), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);
	mScoreText->CreateTextureFromText(std::to_string(mLives));
	mScoreText->Render(Vector2D(220, 50), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);

	if (RectContainsRect(mCamera, mFlag->GetHitbox()))
	{
		mFlag->Render(mCamera);
	}

	for (int i = 0; i < mPlayers.size(); i++)
	{
		mPlayers[i]->Render(mCamera);
	}
	for (int i = 0; i < mBricks.size(); i++)
	{
		if (RectContainsRect(mCamera, mBricks[i]->GetHitbox()) || mBricks[i]->GetDestroyed())
		{
			mBricks[i]->Render(mCamera);
		}
	}
	for (int i = 0; i < mPipes.size(); i++)
	{
		if (RectContainsRect(mCamera, mPipes[i]->GetHitbox()))
		{
			mPipes[i]->Render(mCamera);
		}
	}
	for (int i = 0; i < mCoins.size(); i++)
	{
		if (RectContainsRect(mCamera, mCoins[i]->GetHitbox()))
		{
			mCoins[i]->Render(mCamera);
		}
	}
	for (int i = 0; i < mEnemys.size(); i++)
	{
		if (RectContainsRect(mCamera, mEnemys[i]->GetHitbox()))
		{
			mEnemys[i]->Render(mCamera);
		}
	}

	Debug();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	
	//std::cerr << deltaTime << std::endl;
	if (mLives == 0 )
	{
		ClearLevel();
		mManager->ChangeToGameOver(mScore);
		return;
	}

	if (mResetingLevel)
	{
		ClearLevel();
		SetUpLevel(mPlayerCount);
		return;
	}
	
	CameraMovementLogic();

	if (mCamera->x % 1024 == 0)
	{
		mBackgroundPosition.x = mCamera->x - 1024;
	}

	for (int i = 0; i < mPlayers.size(); i++)
	{
		if (mPlayers[i]->GetX() < 0)
		{
			mPlayers[i]->SetX(0);
		}

		if (mPlayers[i]->GetX() + mPlayers[i]->GetHitbox()->w > mMapTileWidth * DEFAULTTILEWIDTH* RENDERSCALE)
		{
			mPlayers[i]->SetX(mMapTileWidth * DEFAULTTILEWIDTH * RENDERSCALE - mPlayers[i]->GetHitbox()->w);
		}

		if (mPlayers[i]->GetX() < mCamera->x)
		{
			mPlayers[i]->SetX(mCamera->x);
		}

		if (mPlayers[i]->GetX() + mPlayers[i]->GetHitbox()->w > mCamera->x + mCamera->w)
		{
			mPlayers[i]->SetX(mCamera->x + mCamera->w - mPlayers[i]->GetHitbox()->w);
		}

		mPlayers[i]->Update(deltaTime, e);
		
		if (mPlayers[i]->IsAlive())
		{
			bool playerBotCollided = false;
			BrickCollisionsWithPlayer(mPlayers[i], playerBotCollided);
			PipeCollisionsWithPlayer(mPlayers[i], playerBotCollided);
			CoinCollisionsWithPlayer(mPlayers[i]);
			if (!mPlayers[i]->IsInvunerable())
			{
				EnemyCollisionsWithPlayer(mPlayers[i]);
			}
			if (FlagCollisionsWithPlayer(mPlayers[i]))
			{
				return;
			}

			if (!playerBotCollided)
			{
				mPlayers[i]->SetOnPlatform(false);
				mPlayers[i]->SetJumping(true);
				mPlayers[i]->SetPlayerState(PlayerState::JUMP);
			}

			if (mPlayers[i]->GetY() > SCREEN_HEIGHT + 64)
			{
				mPlayers[i]->UpdateHealth(-mPlayers[i]->GetHealth());
			}
		}
		else
		{
			if (mPlayers[i]->GetY() > SCREEN_HEIGHT + 128)
			{
				//std::cerr << "Removing player" << std::endl;
				if (mPlayers.size() > 1)
				{
					mPlayers.erase(mPlayers.begin() + i);
				}
				else
				{
					mPlayers.erase(mPlayers.begin() + i);
					mLives--;
					if (mLives > 0)
					{
						mResetingLevel = true;	
					}
				}
			}
		}
	}
	for (int i = 0; i < mBricks.size(); i++)
	{
		if (RectContainsRect(mCamera, mBricks[i]->GetHitbox()) || mBricks[i]->GetDestroyed())
		{
			mBricks[i]->Update(deltaTime, e, mPlayers, mScore, mCoinsCollected, mCurrentLevel);

			if (mBricks[i]->GetItemInsideSpawned())
			{
				SpawnedItemSolidBlockCollisions(mBricks[i]->GetItemInside());
			}
			if (mBricks[i]->GetDestroyed())
			{
				RemoveDestroyedBricks(mBricks[i], i);
			}
		}
	}
	for (int i = 0; i < mPipes.size(); i++)
	{
		if (RectContainsRect(mCamera, mPipes[i]->GetHitbox()))
		{
			mPipes[i]->Update(deltaTime, e);
		}
	}
	for (int i = 0; i < mCoins.size(); i++)
	{
		if (RectContainsRect(mCamera, mCoins[i]->GetHitbox()))
		{
			mCoins[i]->Update(deltaTime, e, mScore);
		}
	}
	for (int i = 0; i < mEnemys.size(); i++)
	{
		if (RectContainsRect(mCamera, mEnemys[i]->GetHitbox()))
		{
			mEnemys[i]->Update(deltaTime, e);
			EnemyCollisionsWithBlocks(mEnemys[i]);
			if (!mEnemys[i]->IsAlive())
			{
				RemoveDeadEnemies(mEnemys[i], i);
			}
		}
	}
	
	if (RectContainsRect(mCamera, mFlag->GetHitbox()))
	{
		mFlag->Update(deltaTime, e);
	}

	switch (e.type)
	{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_i:
				{
					mEnemys[0]->Killed();
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

void GameScreenLevel1::CameraMovementLogic()
{
	if (mPlayers.size() == 2)
	{
		if (mPlayers.size() == 2)
		{
			if (mPlayers[0]->GetX() > mPlayers[1]->GetX())
			{
				mCamera->x = (mPlayers[1]->GetX() + (mPlayers[1]->GetHitbox()->w / 2) + ((mPlayers[0]->GetX() - mPlayers[1]->GetX())) / 2) - (mCamera->w / 2);
			}
			else
			{
				mCamera->x = (mPlayers[0]->GetX() + (mPlayers[0]->GetHitbox()->w / 2) + ((mPlayers[1]->GetX() - mPlayers[0]->GetX())) / 2) - (mCamera->w / 2);
			}
		}
	}
	else
	{
		mCamera->x = mPlayers[0]->GetX() - (SCREEN_WIDTH / 2);
	}

	if (mCamera->x < 0)
	{
		mCamera->x = 0;
	}
	if (mCamera->y < 0)
	{
		mCamera->y = 0;
	}
	if (mCamera->x + mCamera->w > mMapTileWidth* DEFAULTTILEWIDTH* RENDERSCALE)
	{
		mCamera->x = (mMapTileWidth * DEFAULTTILEWIDTH * RENDERSCALE) - mCamera->w;
	}
	if (mCamera->y < mCamera->h)
	{
		mCamera->y = 0;
	}
}

void GameScreenLevel1::Debug()
{
	if (debug)
	{
		mDebugText->CreateTextureFromText("x: " + std::to_string(mCamera->x) + "y: " + std::to_string(mCamera->y) + "w: " + std::to_string(mCamera->w) + "h: " + std::to_string(mCamera->h));
		mDebugText->Render(Vector2D(10, 100), SDL_FLIP_NONE, RENDERSCALE, mCamera, 0.0f);
		
		for (int i = 0; i < mPlayers.size(); i++)
		{
			mPlayers[i]->Debug(mCamera, mDebugType);
		}
		for (int i = 0; i < mBricks.size(); i++)
		{
			if (RectContainsRect(mCamera, mBricks[i]->GetHitbox()))
			{
				mBricks[i]->Debug(mCamera, mDebugType);
			}
		}
		for (int i = 0; i < mPipes.size(); i++)
		{
			if (RectContainsRect(mCamera, mPipes[i]->GetHitbox()))
			{
				mPipes[i]->Debug(mCamera, mDebugType);
			}
		}
		for (int i = 0; i < mCoins.size(); i++)
		{
			if (RectContainsRect(mCamera, mCoins[i]->GetHitbox()))
			{
				mCoins[i]->Debug(mCamera, mDebugType);
			}
		}
		for (int i = 0; i < mEnemys.size(); i++)
		{
			if (RectContainsRect(mCamera, mEnemys[i]->GetHitbox()))
			{
				mEnemys[i]->Debug(mCamera, mDebugType);
			}
		}

		if (RectContainsRect(mCamera, mFlag->GetHitbox()))
		{
			mFlag->Debug(mCamera, mDebugType);
		}
	}
}

void GameScreenLevel1::BrickCollisionsWithPlayer(Player* player, bool& botCollided)
{
	for (int j = 0; j < mBricks.size(); j++)
	{
		if (RectContainsRect(mCamera, mBricks[j]->GetHitbox()))
		{
			if (player->IsCollidingWith(mBricks[j]))
			{
				switch (mBricks[j]->GetBrickType())
				{
					case BrickType::SECRETBLOCK:
					{
						switch (player->GetSideCollidingWithEntity(mBricks[j]))
						{
							case SIDE::TOP:
							{
								if (player->GetJumpForce() > 0)
								{
									player->SetY(mBricks[j]->GetY() + (mBricks[j]->GetHitbox()->h));
									player->SetJumpForce(0);
									mBumpBlockSound->Play(0);
									mPowerUpSpawnedSound->Play(0);

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

								//Play correct sound
								if (mBricks[j]->GetIfCoinsInside() && !mBricks[j]->GetBeenHit())
								{
									mCoinCollectedSound->Play(1);
								}

								if (player->GetHealth() == 1)
								{
									mBumpBlockSound->Play(0);
								}
								if (player->GetHealth() > 1)
								{
									if (mBricks[j]->GetBrickType() == BrickType::QUESTIONBLOCK)
									{
										mBumpBlockSound->Play(0);
									}
									else
									{
										mBreakBlockSound->Play(0);
									}
								}
								//End sound logic

								if (mBricks[j]->GetItemInside() && !mBricks[j]->GetBeenHit() && (mBricks[j]->GetBrickType() == BrickType::QUESTIONBLOCK))
								{
									mPowerUpSpawnedSound->Play(0);
								}

								mBricks[j]->Hit(player->GetHealth());

								for (int i = 0; i < mCoins.size(); i++)
								{
									if (RectContainsRect(mCoins[i]->GetHitbox(), mBricks[j]->GetTopSensorBox()))
									{
										mScore += 100;
										mCoins.erase(mCoins.begin() + i);
										mCoinCollectedSound->Play(0);
									}
								}

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

			if (RectContainsRect(player->GetBottomSensorBox(), mBricks[j]->GetHitbox()))
			{
				if (mBricks[j]->GetBrickType() != BrickType::SECRETBLOCK)
				{
					botCollided = true;
				}
			}
		}
	}
}

void GameScreenLevel1::PipeCollisionsWithPlayer(Player* player, bool& botCollided)
{
	for (int j = 0; j < mPipes.size(); j++)
	{
		if (RectContainsRect(mCamera, mPipes[j]->GetHitbox()))
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
			if (RectContainsRect(player->GetBottomSensorBox(), mPipes[j]->GetHitbox()))
			{
				botCollided = true;
			}
		}
	}
}

void GameScreenLevel1::CoinCollisionsWithPlayer(Player* player)
{
	for (int i = 0; i < mCoins.size(); i++)
	{
		if (RectContainsRect(mCamera, mCoins[i]->GetHitbox()))
		{
			if (player->IsCollidingWith(mCoins[i]))
			{
				mScore += 200;
				mCoinsCollected++;
				mCoinCollectedSound->Play(0);
				mCoins.erase(mCoins.begin() + i);
			}
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

void GameScreenLevel1::RemoveDeadEnemies(Enemy* enemy, int enemyNum)
{
	if (enemy->CanBeRemoved())
	{
		mEnemys.erase(mEnemys.begin() + enemyNum);
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

		if (RectContainsRect(powerup->GetBottomSensorBox(), mBricks[i]->GetHitbox()))
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
		if (RectContainsRect(powerup->GetBottomSensorBox(), mPipes[j]->GetHitbox()))
		{
			botCollided = true;
		}
	}
	
	if (!botCollided)
	{
		powerup->SetOnPlatform(false);
	}
}

void GameScreenLevel1::EnemyCollisionsWithPlayer(Player* player)
{
	for (int j = 0; j < mEnemys.size(); j++)
	{
		if (mEnemys[j]->IsCollidingWith(player))
		{
			if (mEnemys[j]->IsAlive())
			{
				switch (mEnemys[j]->GetSideCollidingWithEntity(player))
				{
					case RIGHT:
					{
						player->UpdateHealth(-1);
						break;
					}

					case LEFT:
					{
						player->UpdateHealth(-1);
						break;
					}

					case TOP:
					{
						if (player->GetJumpForce() < 0)
						{
							mEnemys[j]->Killed();
							mStompSound->Play(0);
							mScore += 100;
							player->SetJumpForce(300);
						}
						break;
					}

					case BOTTOM:
					{
						player->UpdateHealth(-1);
						break;
					}
				}		
			}
		}
	}
}

void GameScreenLevel1::EnemyCollisionsWithBlocks(Enemy* enemy)
{
	bool botCollided = false;
	for (int i = 0; i < mBricks.size(); i++)
	{

		if (RectContainsRect(mCamera, mBricks[i]->GetHitbox()))
		{
			if (enemy->IsCollidingWith(mBricks[i]))
			{
				switch (mBricks[i]->GetSideCollidingWithEntity(enemy))
				{
					case SIDE::TOP:
					{
						enemy->SetOnPlatform(true);
						break;
					}

					case SIDE::LEFT:
					{
						enemy->SetDirectionFacing(FACING_LEFT);
						break;
					}

					case SIDE::RIGHT:
					{
						enemy->SetDirectionFacing(FACING_RIGHT);
						break;
					}
				}
			}
		}

		if (RectContainsRect(enemy->GetBottomSensorBox(), mBricks[i]->GetHitbox()))
		{
			botCollided = true;
		}
	}

	for (int j = 0; j < mPipes.size(); j++)
	{
		if (RectContainsRect(mCamera, mPipes[j]->GetHitbox()))
		{
			if (enemy->IsCollidingWith(mPipes[j]))
			{
				//player->SetSideHit(player->GetSideCollidingWithEntity(mPipes[j]));
				switch (mPipes[j]->GetSideCollidingWithEntity(enemy))
				{
					case SIDE::TOP:
					{
						enemy->SetOnPlatform(true);
						break;
					}
					case SIDE::LEFT:
					{
						enemy->SetDirectionFacing(FACING_LEFT);
						break;
					}
					case SIDE::RIGHT:
					{
						enemy->SetDirectionFacing(FACING_RIGHT);
						break;
					}
				}
			}
		}
		if (RectContainsRect(enemy->GetBottomSensorBox(), mPipes[j]->GetHitbox()))
		{
			botCollided = true;
		}
	}

	if (!botCollided)
	{
		enemy->SetOnPlatform(false);
	}
}


bool GameScreenLevel1::FlagCollisionsWithPlayer(Player* player)
{
	if (RectContainsRect(mCamera, mFlag->GetHitbox()))
	{
		if (mFlag->IsCollidingWith(player))
		{
			if (mCurrentLevel == 2)
			{
				ClearLevel();
				mManager->ChangeToGameOver(mScore);
				return true;
			}

			//player->SetOnPlatform(true);
			mCurrentLevel++;
			for (int i = 0; i < mPlayers.size(); i++)
			{
				if (!mPlayers[i]->IsAlive())
				{
					mPreviousHealth[i] = 1;
				}
				else
				{
					mPreviousHealth[i] = mPlayers[i]->GetHealth();
				}
			}
			mCourseClearSound->Play(0);
			ClearLevel();
			SetUpLevel(mPlayerCount);
			return true;
		}
	}
	return false;
}
