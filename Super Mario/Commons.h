#pragma once

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
SDL_FORCE_INLINE SDL_bool SDL_RectTest(const SDL_Rect* a, const SDL_Rect* b)
{
	if (a->x + (a->w / 2) >= b->x&&
		a->x + (a->w / 2) <= b->x + b->w &&
		a->y + (a->h / 2) >= b->y&&
		a->y + (a->h / 2) <= b->y + b->h)
	{
		//return SDL_TRUE;
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
	LEFT = 0,
	RIGHT
};
