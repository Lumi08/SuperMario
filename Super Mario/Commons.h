#ifndef _COMMONS_H
#define _COMMONS_H

#include <iostream>
#include <SDL_ttf.h>

enum PlayerState
{
	WALK = 0,
	JUMP,
	IDLE,
	SLEEP
};

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
	BOTTOM,
	NONE
};

enum PowerUpType
{
	MUSHROOM = 0,
	FIREFLOWER
};

enum BrickType
{
	BREAKABLEBLOCK = 0,
	SECRETBLOCK,
	QUESTIONBLOCK,
	SOLIDBLOCK,
	COINBLOCK
};

enum EnemyType
{
	GOOMBA = 0,
	TURTLE
};

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

SDL_FORCE_INLINE SDL_bool RectContainsRect(const SDL_Rect* a, const SDL_Rect* b)
{
	if (a->x + a->w > b->x && a->x < b->x + b->w && a->y + a->h > b->y && a->y < b->y + b->h)
	{
		return SDL_TRUE;
	}

	return SDL_FALSE;
}

SDL_FORCE_INLINE SDL_bool RectContainsVector(const Vector2D p, const SDL_Rect* r)
{
	return ((p.x >= r->x) && (p.x < (r->x + r->w)) &&
		(p.y >= r->y) && (p.y < (r->y + r->h))) ? SDL_TRUE : SDL_FALSE;
}

#endif // !_COMMONS_H
