#ifndef _MAINMENU_H
#define _MAINMENU_H_

#include <SDL.h>

#include "GameScreenManager.h"
#include "GameScreen.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"

struct Button
{
	Texture2D* textTexture;
	int x, y;


	Button(SDL_Renderer* renderer, int x, int y, std::string path)
	{
		this->x = x;
		this->y = y;
		textTexture = new Texture2D(renderer);
		textTexture->LoadFromFile(path.c_str());
	}

	~Button()
	{
		delete textTexture;
	}

	void Render(float scale)
	{
		textTexture->Render(Vector2D(x, y), SDL_FLIP_NONE, scale);
	}
};


class Texture2D;
class MainMenu : GameScreen
{
public:
	MainMenu(SDL_Renderer* renderer, GameScreenManager* manager);
	~MainMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	GameScreenManager* mManager;
	Texture2D* mTitleTexture;
	Texture2D* mGithubTexture;
	Vector2D mTitlePosition;
	Vector2D mGithubPosition;
	Texture2D* mBackgroundTexture;
	Vector2D mBackgroundPosition;
	Button* mStartButton;
	Button* mExitButton;
};

#endif // !_MAINMENU_H


