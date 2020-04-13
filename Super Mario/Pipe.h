#ifndef _PIPE_H
#define _PIPE_H

#include <SDL.h>
#include "Entity.h"

class Pipe : public Entity
{
public:
	Pipe(SDL_Renderer* renderer, std::string imagePath, Vector2D position);
	~Pipe();

	/// Renders the 
	void Render(SDL_Rect* camera);
	void Update(float deltaTime, SDL_Event e);

	///used to make the sure the pipes textures are correct
	void SetSourceRectPos(int x, int y) { mSourceRect->x = x; mSourceRect->y = y; }
	void SetSourceRectPosX(int x) { mSourceRect->x = x; }
	void SetSourceRectPosY(int y) { mSourceRect->y = y; }
private:
	SDL_Rect* mSourceRect;
};


#endif // !_PIPE_H



