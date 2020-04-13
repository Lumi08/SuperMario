#include "GameOver.h"

GameOver::GameOver(SDL_Renderer* renderer, GameScreenManager* manager, int finalScore) : GameScreen(renderer)
{
	mManager = manager;
	
	mBackgroundTexture = new Texture2D(mRenderer);
	mBackgroundTexture->LoadFromFile("Images/Untitled.png");

	mGameOverTexture = new Texture2D(mRenderer);
	mGameOverTexture->LoadFromFile("Images/Menu/GameOver.png");
	mGameOverTexturePosition = Vector2D((SCREEN_WIDTH / 2) - (79 * 6) / 2, 75);

	mTextBackgroundTexture = new Texture2D(mRenderer);
	mTextBackgroundTexture->LoadFromFile("Images/Menu/BlankButton.png");

	mText = new Text(mRenderer, "Font/SMBtext.ttf", SDL_Color{ 255, 204, 128, 255 }, 40);
	mText->CreateTextureFromText("score  " + std::to_string(finalScore));
	mTextPosition = Vector2D(310, 272);

	mMainMenuButton = new Button(mRenderer, (SCREEN_WIDTH / 2) - (79 * 3) / 2, 500, 79 * 3, 16 * 3, "Images/Menu/MainMenu.png");
}

GameOver::~GameOver()
{
	delete mMainMenuButton;
}

void GameOver::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE, 1);
	mGameOverTexture->Render(mGameOverTexturePosition, SDL_FLIP_NONE, 6);
	mTextBackgroundTexture->Render(Vector2D(mGameOverTexturePosition.x, 250), SDL_FLIP_NONE, 6);
	mText->Render(mTextPosition, SDL_FLIP_NONE, 1, NULL, 0);
	mMainMenuButton->Render(3);
}

void GameOver::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		case SDL_MOUSEMOTION:
		{
			mMainMenuButton->Update(e.motion.x, e.motion.y);
			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			if (mMainMenuButton->hovering)
			{
				mManager->ChangeToMenu();
			}
			break;
		}
	}
}
