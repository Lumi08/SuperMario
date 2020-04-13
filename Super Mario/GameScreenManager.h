#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include "Commons.h"

class GameScreen;
class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	/// Render functions for the screens
	void Render();
	/// update functions for the screens
	void Update(float deltaTime, SDL_Event e);
	void ChangeScreen(SCREENS newScreen);
	/// function used to change the current screen
	void ChangeToMenu();
	void ChangeToGameScreen(int numOfPlayers);
	void ChangeToGameOver(int score);
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
};

#endif // !_GAMESCREENMANAGER_H
