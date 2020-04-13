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

	/// Play function
	/// position - Position to play the animation
	/// flip - The flip for the orientation of the animation
	/// camera - The cameras position used to put the animation in the correct place
	/// amgle - Controls the rotation of the animation
	/// timesToLoop - sets the amount of times the animation should loop
	void Play(Vector2D position, SDL_RendererFlip flip, SDL_Rect* camera, double angle = 0, int timesToLoop = 0);
	/// Overloading Play function
	/// No camera as it may be wanted for a animation to not scroll with the camera
	void Play(Vector2D position, SDL_RendererFlip flip, double angle, int timesToLoop = 0);
	
	/// Set the sprite the loop should start from
	void SetLoopStartSprite(int spriteNum);
	/// returns if the animation has completed the first loop
	bool Completed() { return mInitLoopComplete; }
	/// resets the animation
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


