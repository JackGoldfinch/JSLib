//
//  Audio.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 29.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSL_AUDIO_AUDIO_CPP

#include "Audio.hpp"

#include "../Game.hpp"

namespace JSLib {
namespace Audio {

	System::System():
	Util::System ( "Audio" ) {
		/*if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {

		}*/
		
		const ALCchar *devices = nullptr;
		if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT") == ALC_TRUE) {
			devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
		}

		_device = alcOpenDevice(nullptr);

		_context = alcCreateContext(_device, 0);
		alcMakeContextCurrent(_context);

		ALfloat ori[] = { 0.f, 0.f, 0.f, 0.f, 1.f, 0.f };
		alListener3f(AL_POSITION, 0.f, 0.f, 0.f);
		alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f);
		alListenerfv(AL_ORIENTATION, ori);
		//alListenerf(AL_GAIN, 1.f);
		
		started();
	}

	System::~System() {
		stopping();
		
		alcDestroyContext(_context);

		alcCloseDevice(_device);

		//SDL_QuitSubSystem(SDL_INIT_AUDIO);
	}

} /* namespace Audio */
} /* namespace JSLib */
