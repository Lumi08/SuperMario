#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture2D;
class Animation
{
public:
	Animation(SDL_Renderer* renderer, std::string imagePath, SDL_Rect* sourceRectStart, int numberOfFrames, int timePerFrame);
	~Animation();

	void Play(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);
	void SetLoopStartSprite(int spriteNum);
private:
	SDL_Renderer* mRenderer;
	SDL_Rect* mSourceRect;
	Texture2D* mTexture;
	Vector2D* mSourceRectStartPoint;
	int mNumberOfFrames,
		mTimePerFrame,
		mCurrentFrameTime,
		mSpriteLoopStartSprite = 0;
	bool mInitLoopComplete = false;

};

#endif // !_ANIMATION_H_


