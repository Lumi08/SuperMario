#ifndef _MAINMENU_H
#define _MAINMENU_H_

#include <SDL.h>

#include "GameScreenManager.h"
#include "GameScreen.h"
#include "Commons.h"
#include "Constants.h"
#include "Ui.h"

class Texture2D;
class MainMenu : GameScreen
{
public:
	MainMenu(SDL_Renderer* renderer, GameScreenManager* manager);
	~MainMenu();

	/// Main menus render function which calls all render functionss for the assets on that screen
	void Render();
	/// main menu update function which calls all the update functions for the assets on that screen
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


