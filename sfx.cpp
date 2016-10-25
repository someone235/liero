#include "sfx.hpp"
#include "reader.hpp"
#include "console.hpp"
#include "common.hpp"
#include <vector>
#include <cassert>
#if !DISABLE_SOUND
#include <SDL/SDL.h>
#endif
//#include <iostream>

//#include <cmath> // TEMP

Sfx sfx;

extern "C" void SDLCALL Sfx_callback(void *userdata, Uint8 *stream, int len)
{
	uint32 frame_count = len / 2;

	sfx_mixer_mix((sfx_mixer*)userdata, stream, frame_count);
}

void Sfx::init()
{
	return;
#if !DISABLE_SOUND
	if(initialized)
		return;
	
	SDL_InitSubSystem(SDL_INIT_AUDIO);

	mixer = sfx_mixer_create();

	SDL_AudioSpec spec;
	memset(&spec, 0, sizeof(spec));
	spec.channels = 1;
	spec.freq = 44100;
	spec.format = AUDIO_S16SYS;
	spec.size = 4*512;
	spec.callback = Sfx_callback;
	spec.userdata = mixer;
	
	int ret = SDL_OpenAudio(&spec, NULL);
	
	if(ret == 0)
	{
		initialized = true;
		//Mix_AllocateChannels(8);
		//Mix_Volume(-1, 128);
		SDL_PauseAudio(0);
	}
	else
	{
		Console::writeWarning(std::string("SDL_OpenAudio returned error: ") + SDL_GetError());
	}
#endif
}

void Sfx::deinit()
{
#if !DISABLE_SOUND
	if(!initialized)
		return;
	initialized = false;

	//Mix_CloseAudio();
	SDL_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
#endif
}
/*
void Sfx::loadFromSND()
{
#if !DISABLE_SOUND
	ReaderFile& snd = openLieroSND();
		
	int count = readUint16(snd);
	
	sounds.resize(count);
	
	long oldPos = snd.tellg();
	
	for(int i = 0; i < count; ++i)
	{
		snd.seekg(oldPos + 8);
		
		int offset = readUint32(snd);
		int length = readUint32(snd);
		
		oldPos = snd.tellg();
		
		int byteLength = length * 4;

		sounds[i] = sfx_new_sound(byteLength / 2);
		
		int16_t* ptr = reinterpret_cast<int16_t*>(sfx_sound_data(sounds[i]));
		
		std::vector<uint8_t> temp(length);
		
		if(length > 0)
		{
			snd.seekg(offset);
			snd.get(&temp[0], length);
		}
		
		int prev = ((int8_t)temp[0]) * 30;
		*ptr++ = prev;
		
		for(int j = 1; j < length; ++j)
		{
			int cur = (int8_t)temp[j] * 30;
			*ptr++ = (prev + cur) / 2;
			*ptr++ = cur;
			prev = cur;
		}
		
		*ptr++ = prev;
	}
#endif

}*/

void Sfx::play(Common& common, int sound, void* id, int loops)
{
#if !DISABLE_SOUND
	if(!initialized)
		return;

	sfx_mixer_add(mixer, common.sounds[sound], sfx_mixer_now(mixer), id, loops ? SFX_SOUND_LOOP : SFX_SOUND_NORMAL);
#endif
}

void Sfx::stop(void* id)
{
#if !DISABLE_SOUND
	if(!initialized)
		return;

	sfx_mixer_stop(mixer, id);
#endif
}

bool Sfx::isPlaying(void* id)
{
#if !DISABLE_SOUND
	if(!initialized)
		return false;

	return sfx_is_playing(mixer, id) != 0;
#else
	return false;
#endif
}

Sfx::~Sfx()
{
	deinit();

#if !DISABLE_SOUND
/*
	for(std::size_t i = 0; i < sounds.size(); ++i)
	{
		sfx_free_sound(sounds[i]);
	}*/
#endif
}
