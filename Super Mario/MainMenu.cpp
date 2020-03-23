#include "MainMenu.h"
#include "Texture2D.h"

MainMenu::MainMenu(SDL_Renderer* renderer, GameScreenManager* manager) : GameScreen(renderer)
{
	mManager = manager;
	mTitleTexture = new Texture2D(mRenderer);
	mBackgroundTexture = new Texture2D(mRenderer);
	mGithubTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/untitled.png"))
	{
		std::cout << "Error: Failed to load background texture!" << std::endl;
	}

	if (!mGithubTexture->LoadFromFile("Images/Menu/Github.png"))
	{
		std::cout << "Error: Failed to load background texture!" << std::endl;
	}

	if (!mTitleTexture->LoadFromFile("Images/Menu/Title.png"))
	{
		std::cout << "Error: Failed to load title texture!" << std::endl;
	}

	mTitlePosition = Vector2D((SCREEN_WIDTH/2) - (174*3)/2, 75);
	mGithubPosition = Vector2D((SCREEN_WIDTH / 2) - (164 * 3) / 2, 700);
	mBackgroundPosition = Vector2D(0, 0);

	mStartButton = new Button(mRenderer, (SCREEN_WIDTH / 2) - (48 * 3) / 2, 400, "Images/Menu/StartButton.png");
	mExitButton = new Button(mRenderer, (SCREEN_WIDTH / 2) - (48 * 3) / 2, 500, "Images/Menu/ExitButton.png");
}

MainMenu::~MainMenu()
{
	delete mStartButton;
	delete mExitButton;
	delete mTitleTexture;
	delete mGithubTexture;
	delete mBackgroundTexture;
}

void MainMenu::Render()
{
	mBackgroundTexture->Render(mBackgroundPosition, SDL_FLIP_NONE, 1);
	mTitleTexture->Render(mTitlePosition, SDL_FLIP_NONE, 3);
	mGithubTexture->Render(mGithubPosition, SDL_FLIP_NONE, 3);
	mStartButton->Render(3);
	mExitButton->Render(3);
}

void MainMenu::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_SPACE:
				{
					mManager->ChangeScreen(SCREEN_LEVEL1);
					//this->~MainMenu();
					break;
				}
			}
			break;
		}

	}
}
