#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SDL.h>
#include <string>

#include "Commons.h"

class Texture2D;
class Entity
{
public:
	Entity(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Entity();
	
	virtual void Render();
	virtual void Update();

protected:
	SDL_Renderer* mRenderer;
	Texture2D* mTexture;
	Vector2D mPosition;
};

#endif // !_ENTITY_H_
