#ifndef _COMMONS_H
#define _COMMONS_H

#include <iostream>

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

//bool Overlapping(SDL_Rect* rect1, SDL_Rect* rect2)
//{
//	return true;
//}
SDL_FORCE_INLINE SDL_bool RectIntersects(const SDL_Rect* a, const SDL_Rect* b, int &sideHit)
{
	//Left
	if (a->x > b->x + b->w)
	{
		sideHit = 2;
	}
	//Top
	if (a->y > b->y + b->h)
	{
		sideHit = 4;
	}
	//Right
	if (a->x + a->w < b->x)
	{
		sideHit = 1;
	}
	//Bottom
	if (a->y + a->h < b->y)
	{
		sideHit = 3;
	}

	if (a->x + a->w > b->x && a->x < b->x + b->w && a->y + a->h > b->y && a->y < b->y + b->h)
	{
		return SDL_TRUE;
	}

	return SDL_FALSE;
}

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum SIDE
{
	LEFT = 0,
	TOP,
	RIGHT,
	BOTTOM
};

#endif // !_COMMONS_H
