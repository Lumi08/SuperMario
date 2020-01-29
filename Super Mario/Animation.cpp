#include "Animation.h"
#include "Texture2D.h"

Animation::Animation(SDL_Renderer* renderer, std::string imagePath, SDL_Rect* sourceRectStart, int numberOfFrames, int timePerFrame)
{
	this->mRenderer = renderer;
	this->mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mSourceRectStartPoint = new Vector2D(sourceRectStart->x, sourceRectStart->y);
	this->mSourceRect = sourceRectStart;
	this->mNumberOfFrames = numberOfFrames;
	this->mTimePerFrame = timePerFrame;
	mCurrentFrameTime = 0;
}

Animation::~Animation()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
}

void Animation::Play(Vector2D position, SDL_RendererFlip flip, double angle)
{
	if (mCurrentFrameTime >= mTimePerFrame)
	{
		if (mSourceRect->x != (mSourceRect->w * (mNumberOfFrames - 1)))
		{
			mSourceRect->x += mSourceRect->w;
		}
		else
		{
			if (mSpriteLoopStartSprite != 0)
			{
				mSourceRect->x = mSourceRectStartPoint->x + ((mSpriteLoopStartSprite - 1) * mSourceRect->w);
			}
			else 
			{
				mSourceRect->x = mSourceRectStartPoint->x;
			}

			mSourceRect->y = mSourceRectStartPoint->y;
		}
		mCurrentFrameTime = 0;
	}
	mCurrentFrameTime++;


	mTexture->Render(position, flip, 0.0f, mSourceRect);
}

void Animation::SetLoopStartSprite(int spriteNum)
{
	mSpriteLoopStartSprite = spriteNum;
}

