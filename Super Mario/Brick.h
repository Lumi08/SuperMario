#ifndef _BRICK_H
#define	_BRICK_H

#include <SDL.h>
#include <string>
#include "Entity.h"

class Brick : public Entity
{
public:
	Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position);
	~Brick();
	void Update(float deltaTime, SDL_Event e, Player* mario, Player* Luigi);
	void Render();
private:
	SDL_Rect* mSourceRect;
	void CollisionsWithPlayer(Player* player);
};

#endif // !_BRICK_H


