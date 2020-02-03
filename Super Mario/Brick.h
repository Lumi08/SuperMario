#ifndef _BRICK_H
#define	_BRICK_H

#include <SDL.h>
#include <string>
#include "Entity.h"

class Brick : public Entity
{
public:
	Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, float renderScale);
	~Brick();
	void Update(float deltaTime, SDL_Event e);
	void Render();
private:
	SDL_Rect* mSourceRect;
};

#endif // !_BRICK_H


