#ifndef _ENEMY_H
#define _ENEMY_H

#include <SDL.h>
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(SDL_Renderer* renderer, std::string imgPath, Vector2D spawnLocation, int width, int height);
	~Enemy();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:

};

#endif // !_ENEMY_H



