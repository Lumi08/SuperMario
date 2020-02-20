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
	//mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	for (int i = 0; i < 2; i++)
	{
		mPlayers[i]->Render();
	}
	for (int i = 0; i < mBrickCount; i++)
	{
		mBricks[i]->Render();
	}
	
	if (debug)
	{
		for (int i = 0; i < 2; i++)
		{
			mPlayers[i]->Debug();
		}
		for (int i = 0; i < mBrickCount; i++)
		{
			mBricks[i]->Debug();
		}
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	for (int i = 0; i < 2; i++)
	{
		mPlayers[i]->Update(deltaTime, e);
	}
	for (int i = 0; i < mBrickCount; i++)
	{
		mBricks[i]->Update(deltaTime, e, mPlayers);
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
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	/*mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Error: Failed to load background texture!" << std::endl;
		return false;
	}*/
	MapLoader* map = new MapLoader((char*)"map1.txt", mRenderer);
	map->LoadMapAssets(mPlayers, mBricks);

	mBrickCount = map->GetActualBrickCount();

	mPlayers[0] = new Player(mRenderer, "Images/Mario.png", Vector2D(64, 330), 1);
	mPlayers[1] = new Player(mRenderer, "Images/Luigi.png", Vector2D(64, 250), 2);
	//SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	return true;
	//mCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));
}
