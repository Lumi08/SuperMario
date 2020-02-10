#include "Animation.h"
#include "Texture2D.h"

Animation::Animation(SDL_Renderer* renderer, Texture2D* texture, SDL_Rect* sourceRectStart, int numberOfFrames, int timePerFrame, float renderScale)
{
	this->mRenderer = renderer;
	this->mTexture = texture;
	mSourceRectStartPoint = new Vector2D(sourceRectStart->x, sourceRectStart->y);
	this->mSourceRect = sourceRectStart;
	this->mNumberOfFrames = numberOfFrames;
	this->mTimePerFrame = timePerFrame;
	mCurrentFrameTime = 0;
	mRenderScale = renderScale;
}

Animation::~Animation()
{
	mRenderer = NULL;
}

void Animation::Play(Vector2D position, SDL_RendererFlip flip, double angle, int timesToLoop)
{

	if (mCurrentFrameTime >= mTimePerFrame)
	{
		if (mSourceRect->x != (mSourceRect->w * (mNumberOfFrames - 1)))
		{
			mSourceRect->x += mSourceRect->w;
		}
		else
		{
			if (mTimesLooped != timesToLoop || timesToLoop == 0)
			{

			}
			if (mSpriteLoopStartSprite != 0)
			{
				mSourceRect->x = mSourceRectStartPoint->x + ((mSpriteLoopStartSprite - 1) * mSourceRect->w);
			}
			else
			{
				mSourceRect->x = mSourceRectStartPoint->x;
			}
			mTimesLooped++;
			mSourceRect->y = mSourceRectStartPoint->y;
		}
		mCurrentFrameTime = 0;
	}
	mCurrentFrameTime++;


	mTexture->Render(position, flip, mRenderScale, 0.0f, mSourceRect);
}

void Animation::SetLoopStartSprite(int spriteNum)
{
	mSpriteLoopStartSprite = spriteNum;
}

