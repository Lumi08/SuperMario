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

	/// Renders the coins textures
	void Render(SDL_Rect* camera);
	///Updates the coins information
	void Update(float deltaTime, SDL_Event e, int& score);
private:
	Animation* mAnimation;
	SDL_Rect* mSourceRect;
};

#endif // !_COIN_H