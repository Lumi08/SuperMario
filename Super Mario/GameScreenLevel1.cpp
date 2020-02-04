 #include "GameScreenLevel1.h"
#include <iostream>
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
	mMario->Render();
	mLuigi->Render();
	mBrick->Render();
	if (debug)
	{
		mBrick->Debug();
		mMario->Debug();
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mMario->Update(deltaTime, e);
	mLuigi->Update(deltaTime, e);
	mBrick->Update(deltaTime, e);
	//int int1;
	//std::cout << mMario->GetOnPlatform() << std::endl;
	if (RectIntersects(mBrick->GetHitbox(), mMario->GetHitbox(), int1))
	{
		if (int1 == 4)
		{
			mMario->SetY(mBrick->GetY() - mMario->GetHeight());
			mMario->SetOnPlatform(true);
		}
		if (int1 == 3)
		{
			mMario->SetY(mBrick->GetY() + mBrick->GetHeight());
			mMario->SetOnPlatform(false);
			mMario->SetJumpForce(0);
		}
		if (int1 == 2)
		{
			mMario->SetX(mBrick->GetX() - mMario->GetWidth());
			mMario->SetOnPlatform(false);
		}
		if (int1 == 1)
		{
			mMario->SetX(mBrick->GetX() + mBrick->GetWidth());
			mMario->SetOnPlatform(false);
		}
	}
	if (mMario->GetX() > mBrick->GetX() + mBrick->GetWidth() ||
		mMario->GetX() + mMario->GetWidth() < mBrick->GetX())
	{
		mMario->SetOnPlatform(false);
	}
	//std::cout << int1 << std::endl;

	switch (e.type)
	{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_i:
				{
					mMario->SetX(100);
					mMario->SetY(100);
				}

				case SDLK_F3:
				{	
					debug = !debug;
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
	mMario = new Player(mRenderer, "Images/Mario.png", Vector2D(64, 330), 2, 1);
	mLuigi = new Player(mRenderer, "Images/Luigi.png", Vector2D(64, 250), 2, 2);
	mBrick = new Brick(mRenderer, "Images/Brick.png", Vector2D(500, 850), 2);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	return true;
	//mCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));
}
