#ifndef _MAINMENU_H
#define _MAINMENU_H_

#include <SDL.h>

#include "GameScreenManager.h"
#include "GameScreen.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Animation.h"

struct Button
{
	SDL_Renderer* renderer;
	Texture2D* textTexture;
	Texture2D* hoveringImage;
	Animation* hoveringAnimation;
	SDL_Rect* hitbox;
	bool hovering;

	Button(SDL_Renderer* renderer, int x, int y, int width, int height, std::string path)
	{
		this->renderer = renderer;
		hitbox = new SDL_Rect{ x, y, width, height };
		textTexture = new Texture2D(renderer);
		textTexture->LoadFromFile(path.c_str());
		hoveringImage = new Texture2D(renderer);
		hoveringImage->LoadFromFile("Images/Mario.png");
		hoveringAnimation = new Animation(renderer, hoveringImage, new SDL_Rect{ 0, 0, DEFAULTTILEWIDTH, DEFAULTTILEHEIGHT }, 2, 1000, RENDERSCALE);
		hovering = false;
	}

	~Button()
	{
		delete textTexture;
	}

	void Render(float scale)
	{
		textTexture->Render(Vector2D(hitbox->x, hitbox->y), SDL_FLIP_NONE, scale);
		if (hovering)
		{
			hoveringAnimation->Play(Vector2D(hitbox->x - 50, hitbox->y + 8), SDL_FLIP_HORIZONTAL, 0.0f);
			hoveringAnimation->Play(Vector2D(hitbox->x + hitbox->w + 50 - 32, hitbox->y + 8), SDL_FLIP_NONE, 0.0f);
			//hoveringImage->Render(Vector2D(hitbox->x - 50, hitbox->y + 8), SDL_FLIP_NONE, 2);
			//hoveringImage->Render(Vector2D(hitbox->x + hitbox->w + 50 - 32, hitbox->y + 8), SDL_FLIP_NONE, 2);
		}
	}

	void Update(int mouseX, int mouseY)
	{
		if (RectContainsVector(Vector2D(mouseX, mouseY), hitbox))
		{
			hovering = true;
		}
		else
		{
			hovering = false;
		}
	}

	void Debug()
	{
		SDL_RenderDrawRect(renderer, hitbox);
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
	Button* mGithubButton;
	Button* mOnePlayerButton;
	Button* mTwoPlayerButton;
	bool mPlayerSelect;
};

#endif // !_MAINMENU_H


