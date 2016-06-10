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
		
		{
			Game::log << "-- Initialising OpenAL with ALC:\n";
			
			ALint major, minor;
			alcGetIntegerv(_device, ALC_MAJOR_VERSION, 1, &major);
			alcGetIntegerv(_device, ALC_MINOR_VERSION, 1, &minor);
			Game::log << "\tALC version: " << major << "." << minor << "\n";
			
			if (alcIsExtensionPresent(nullptr, "ALC_enumeration_EXT") == ALC_TRUE) {
				const ALCchar *devices = nullptr;
				
				if (alcIsExtensionPresent(nullptr, "ALC_enumerate_all_EXT") == ALC_TRUE) {
					devices = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
				} else {
					devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
				}
				
				Game::log << "\t+ Devices:";
				if (devices) {
					std::stringstream ss(devices);
					std::string line;
					int i = 1;
					while (std::getline(ss, line, '\0')) {
						Game::log << "\n\t\t- (" << i++ << ") " << line;
					}
				}
			}
			
			Game::log << std::endl;
		}

		_device = alcOpenDevice(nullptr);
		
		if(!_device) {
			throw false;
		}

		_context = alcCreateContext(_device, 0);
		if (!_context) {
			throw false;
		}
		
		alcMakeContextCurrent(_context);
		
		{
			Game::log << "-- OpenAL context created on device '" << alcGetString(_device, ALC_DEVICE_SPECIFIER) << "':\n";
			Game::log << "\t" << alGetString(AL_VENDOR) << "(" << alGetString(AL_RENDERER) << " " << alGetString(AL_VERSION) << ")\n";
			
			Game::log << "\t+ Extensions:";
			auto alExtensions = alGetString(AL_EXTENSIONS);
			auto alcExtensions = alcGetString(_device, ALC_EXTENSIONS);
			if (alExtensions || alcExtensions) {
				int i = 1;
				
				std::string line;
				if (alcExtensions) {
					std::stringstream ss(alcExtensions);
					
					while (std::getline(ss, line, (char)0x20)) {
						Game::log << "\n\t\t- (" << i++ << ") " << line;
					}
				}
				
				if (alExtensions) {
					std::stringstream ss(alExtensions);
					
					while (std::getline(ss, line, (char)0x20)) {
						Game::log << "\n\t\t- (" << i++ << ") " << line;
					}
				}
				
			} else {
				Game::log << "\n\tNone.";
			}
			
			Game::log << std::endl;
		}

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
