#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void update(float deltaTime, SDL_Event e);

private:
	SDL_Renderer* mRenderer
};

#endif // !_GAMESCREEN_H