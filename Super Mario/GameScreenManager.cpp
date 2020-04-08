#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "MainMenu.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	this->mRenderer = renderer;
	mCurrentScreen = NULL;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen, int numOfPlayers)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempLevel1Screen;
	MainMenu* tempMainMenu;

	switch (newScreen)
	{
		case SCREEN_LEVEL1:
		{
			tempLevel1Screen = new GameScreenLevel1(mRenderer, numOfPlayers);
			mCurrentScreen = (GameScreen*)tempLevel1Screen;
			tempLevel1Screen = NULL;
			break;
		}

		case SCREEN_MENU:
		{
			tempMainMenu = new MainMenu(mRenderer, this);
			mCurrentScreen = (GameScreen*)tempMainMenu;
			tempMainMenu = NULL;
			break;
		}
	}
}
