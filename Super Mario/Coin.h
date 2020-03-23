#ifndef _COIN_H
#define _COIN_H

#include <SDL.h>
#include "Entity.h"
#include "Commons.h"
#include "Animation.h"
#include "Player.h"

class Coin : public Entity
{
public:
	Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D position);
	~Coin();

	void Render(SDL_Rect* camera);
	void Update(float deltaTime, SDL_Event e, int& score);
private:
	SDL_Renderer* mRenderer;
	Animation* mAnimation;
	SDL_Rect* mSourceRect;
};

#endif // !_COIN_H