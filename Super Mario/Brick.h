#ifndef _BRICK_H
#define	_BRICK_H

#include <SDL.h>
#include <string>

#include "Player.h"
#include "Entity.h"
#include "Mushroom.h"

class Brick : public Entity
{
public:
	Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, float renderScale);
	~Brick();
	
	void Update(float deltaTime, SDL_Event e, Player* player, int numOfPlayers);
	void Render();
	void PlayerCollisions(Player* player);
private:
	SDL_Rect* mSourceRect;
	Mushroom* mMushroom;
};

#endif // !_BRICK_H


