#ifndef _SOUNDEFFECT_H
#define _SOUNDEFFECT_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>

class SoundEffect
{
public:
	SoundEffect(std::string path);
	~SoundEffect();

	void Play(int timesToLoop);

private:
	Mix_Chunk* mSound;
};


#endif // !_SOUNDEFFECT_H