#ifndef _COMMONS_H
#define _COMMONS_H

#include <iostream>

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
SDL_FORCE_INLINE SDL_bool RectIntersects(const SDL_Rect* a, const SDL_Rect* b, SIDE &sideHit)
{

	//std::cout << sideHit << std::endl;

	if (a->x + a->w > b->x && a->x < b->x + b->w && a->y + a->h > b->y && a->y < b->y + b->h)
	{
		return SDL_TRUE;
	}

	return SDL_FALSE;
}

SDL_FORCE_INLINE SDL_bool RectIntersects(const SDL_Rect* a, const SDL_Rect* b)
{
	if (a->x + a->w >= b->x && a->x <= b->x + b->w && a->y + a->h >= b->y && a->y <= b->y + b->h)
	{
		return SDL_TRUE;
	}

	return SDL_FALSE;
}

SDL_FORCE_INLINE SIDE RectGetSideHit(const SDL_Rect* a, const SDL_Rect* b, float deltaTime, SDL_Renderer* renderer)
{
	int sensorsize = 5;
	SDL_Rect* left = new SDL_Rect{ a->x - sensorsize, a->y - 1, sensorsize, a->h +1 };
	SDL_Rect* right = new SDL_Rect{ a->x + a->w, a->y + 1, sensorsize, a->h + 1 };
	SDL_Rect* top = new SDL_Rect{ a->x, a->y - sensorsize, a->w, sensorsize };
	SDL_Rect* bottom = new SDL_Rect{ a->x + 1, a->y + a->h, a->w - 2, sensorsize };

	if (RectIntersects(b, left))
	{
		//std::cerr << "Left" << std::endl;
		return SIDE::LEFT;
	}
	if (RectIntersects(b, right))
	{
		//std::cerr << "Right" << std::endl;
		return SIDE::RIGHT;
	}
	if (RectIntersects(b, top))
	{
		//std::cerr << "Top" << std::endl;
		return SIDE::TOP;
	}
	if (RectIntersects(b, bottom))
	{
		//std::cerr << "Bottom" << std::endl;
		return SIDE::BOTTOM;
	}
	
	
	return NONE;
}



#endif // !_COMMONS_H
