#ifndef _FLAG_H
#define _FLAG_H

#include <SDL.h>
#include <vector>

#include "Texture2D.h"
#include "Entity.h"

//#define MAXPOLEHEIGHT 10

class Flag : public Entity
{
public:
	Flag(SDL_Renderer* renderer, std::string path, Vector2D position);
	~Flag();

	void Render(SDL_Rect* camera);
	void Update(float deltatime, SDL_Event e);
	void AddSection(int x, int y);
	void Clear();
private:
	SDL_Rect* mSourceRect;
	std::vector<Vector2D> mPolePos;
};

#endif // !_FLAG_H