#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>

class GameScreen
{
protected:
	SDL_Renderer* mRenderer;
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	/// Main render function which will call all the other render functions inside of the entity and other external calasses which will be on the gamescreen
	virtual void Render();
	/// Main update function which will call all other update functions for the classes being used in the gamescreen
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif // _GAMESCREEN_H

