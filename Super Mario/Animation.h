#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture2D;
class Animation
{
public:
	Animation(SDL_Renderer* renderer, Texture2D* texture, SDL_Rect* sourceRectStart, int numberOfFrames, int timePerFrame, float renderScale);
	~Animation();

	void Play(Vector2D position, SDL_RendererFlip flip, SDL_Rect* camera, double angle = 0, int timesToLoop = 0);

	void Play(Vector2D position, SDL_RendererFlip flip, double angle, int timesToLoop = 0);

	void SetLoopStartSprite(int spriteNum);
	bool Completed() { return mInitLoopComplete; }
	void Reset() { mInitLoopComplete = false; }
private:
	SDL_Renderer* mRenderer;
	SDL_Rect* mSourceRect;
	Texture2D* mTexture;
	Vector2D* mSourceRectStartPoint;
	int mNumberOfFrames,
		mTimePerFrame,
		mCurrentFrameTime,
		mSpriteLoopStartSprite = 0,
		mTimesLooped = -1;
	float mRenderScale;
	bool mInitLoopComplete;

};

#endif // !_ANIMATION_H_


