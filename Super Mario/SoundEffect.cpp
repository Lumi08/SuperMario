#include "SoundEffect.h"


SoundEffect::SoundEffect(std::string path)
{
	mSound = Mix_LoadWAV(path.c_str());

	if (mSound == NULL)
	{
		std::cout << "Error Loading: " << path << " Error: " << Mix_GetError() << std::endl;
	}
}

SoundEffect::~SoundEffect()
{
	if (mSound != NULL)
	{
		Mix_FreeChunk(mSound);
	}
}

void SoundEffect::Play(int timesToLoop)
{
	int mchannel = Mix_PlayChannel(-1, mSound, timesToLoop);
}
