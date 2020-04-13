#ifndef _COMMONS_H
#define _COMMONS_H

#include <iostream>
//#include <SDL_ttf.h>

/// Player states. used to determine what logic should run for each state in the player class
enum PlayerState
{
	WALK = 0,
	JUMP,
	IDLE,
	SLEEP,
	DEAD
};

/// Used to change the screens using the GameScreen Manager class
enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

/// Used to determine which direction a entity is facing
enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

/// Used to determine which side of a quare has been hitten
enum SIDE
{
	LEFT = 0,
	TOP,
	RIGHT,
	BOTTOM,
	NONE
};

/// The powerups currently in the game
enum PowerUpType
{
	MUSHROOM = 0,
	FIREFLOWER
};

/// The brick types currently in the game, this is used to determine how a brick acts
enum BrickType
{
	BREAKABLEBLOCK = 0,
	SECRETBLOCK,
	QUESTIONBLOCK,
	SOLIDBLOCK,
	COINBLOCK
};

/// The different types of enemys, this determines how an enemy should act
enum EnemyType
{
	GOOMBA = 0,
	TURTLE
};

/// Vector 2d is used to stor the x and y coords for entity positions
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

/// Hitbox logic. check whether 2 rects are intersecting
SDL_FORCE_INLINE SDL_bool RectContainsRect(const SDL_Rect* a, const SDL_Rect* b)
{
	if (a->x + a->w > b->x && a->x < b->x + b->w && a->y + a->h > b->y && a->y < b->y + b->h)
	{
		return SDL_TRUE;
	}

	return SDL_FALSE;
}

/// Checks if a vector is inside of a rect
SDL_FORCE_INLINE SDL_bool RectContainsVector(const Vector2D p, const SDL_Rect* r)
{
	return ((p.x >= r->x) && (p.x < (r->x + r->w)) &&
		(p.y >= r->y) && (p.y < (r->y + r->h))) ? SDL_TRUE : SDL_FALSE;
}

#endif // !_COMMONS_H
