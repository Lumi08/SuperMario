#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "MainMenu.h"
#include "GameOver.h"

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

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempLevel1Screen;
	GameOver* tempGameOver;
	MainMenu* tempMainMenu;

	switch (newScreen)
	{
		case SCREEN_MENU:
		{
			tempMainMenu = new MainMenu(mRenderer, this);
			mCurrentScreen = (GameScreen*)tempMainMenu;
			tempMainMenu = NULL;
			break;
		}
	}
}

void GameScreenManager::ChangeToMenu()
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	MainMenu* tempMainMenu;
	tempMainMenu = new MainMenu(mRenderer, this);
	mCurrentScreen = (GameScreen*)tempMainMenu;
	tempMainMenu = NULL;
}

void GameScreenManager::ChangeToGameScreen(int numOfPlayers)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempLevel1Screen;
	tempLevel1Screen = new GameScreenLevel1(mRenderer, this, numOfPlayers);
	mCurrentScreen = (GameScreen*)tempLevel1Screen;
	tempLevel1Screen = NULL;
}

void GameScreenManager::ChangeToGameOver(int score)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameOver* tempGameOver;
	tempGameOver = new GameOver(mRenderer, this, score);
	mCurrentScreen = (GameScreen*)tempGameOver;
	tempGameOver = NULL;
}
