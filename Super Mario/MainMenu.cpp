#include "MainMenu.h"
#include "Texture2D.h"

MainMenu::MainMenu(SDL_Renderer* renderer, GameScreenManager* manager) : GameScreen(renderer)
{
	mManager = manager;
	mTitleTexture = new Texture2D(mRenderer);
	mBackgroundTexture = new Texture2D(mRenderer);
	mGithubTexture = new Texture2D(mRenderer);
	mPlayerSelect = false;

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

	mSelectedSound = new SoundEffect("Audio/coin collected.wav");

	mTitlePosition = Vector2D((SCREEN_WIDTH/2) - (174*3)/2, 75);
	mGithubPosition = Vector2D((SCREEN_WIDTH / 2) - (164 * 3) / 2, 700);
	mBackgroundPosition = Vector2D(0, 0);

	mStartButton = new Button(mRenderer, (SCREEN_WIDTH / 2) - (48 * 3) / 2, 400, 48 * 3, 16 * 3, "Images/Menu/StartButton.png");
	mExitButton = new Button(mRenderer, (SCREEN_WIDTH / 2) - (48 * 3) / 2, 500, 48 * 3, 16 * 3, "Images/Menu/ExitButton.png");
	mGithubButton = new Button(mRenderer, (SCREEN_WIDTH / 2) - (164 * 3) / 2, 700, 164 * 3, 16 * 3, "Images/Menu/Github.png");
	mOnePlayerButton = new Button(mRenderer, (SCREEN_WIDTH / 2) - (100 * 3) / 2, 400, 100 * 3, 16 * 3, "Images/Menu/SinglePlayerButton.png");
	mTwoPlayerButton = new Button(mRenderer, (SCREEN_WIDTH / 2) - (82 * 3) / 2, 500, 82 * 3, 16 * 3, "Images/Menu/TwoPlayerButton.png");
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
	mGithubButton->Render(3);
	
	if (!mPlayerSelect)
	{
		mStartButton->Render(3);
		mExitButton->Render(3);
	}
	else
	{
		mOnePlayerButton->Render(3);
		mTwoPlayerButton->Render(3);
	}
}

void MainMenu::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		case SDL_MOUSEMOTION:
		{
			mGithubButton->Update(e.motion.x, e.motion.y);
			if (!mPlayerSelect)
			{
				mStartButton->Update(e.motion.x, e.motion.y);
				mExitButton->Update(e.motion.x, e.motion.y);
			}
			else
			{
				mOnePlayerButton->Update(e.motion.x, e.motion.y);
				mTwoPlayerButton->Update(e.motion.x, e.motion.y);
			}
			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			if (mStartButton->hovering)
			{
				mPlayerSelect = true;
				mSelectedSound->Play(0);
			}

			if (mGithubButton->hovering)
			{
				mSelectedSound->Play(0);
				std::cout << "GitHub" << std::endl;

				try
				{
					system("start chrome https://ryangoldsmith.github.io/");
				}
				catch(const std::exception& e)
				{
					system("start iexplore https://ryangoldsmith.github.io/");
				}
			}

			if (mExitButton->hovering)
			{
				mSelectedSound->Play(0);
				std::cout << "Exit" << std::endl;
				SDL_Quit();
				exit(0);
			}

			if (mOnePlayerButton->hovering)
			{
				mSelectedSound->Play(0);
				mManager->ChangeToGameScreen(1);
				break;
			}

			if (mTwoPlayerButton->hovering)
			{
				mSelectedSound->Play(0);
				mManager->ChangeToGameScreen(2);
				break;
			}
			break;
		}
	}
}
