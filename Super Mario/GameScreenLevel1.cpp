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
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mMario->Update(deltaTime, e);
	mLuigi->Update(deltaTime, e);
	mBrick->Update(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel()
{
	/*mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Error: Failed to load background texture!" << std::endl;
		return false;
	}*/
	mMario = new Player(mRenderer, "Images/Mario.png", Vector2D(64, 330), 1);
	mLuigi = new Player(mRenderer, "Images/Luigi.png", Vector2D(64, 250), 2);
	mBrick = new Brick(mRenderer, "Images/Brick.png", Vector2D(500, 800));
	
	return true;
	//mCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));
}
