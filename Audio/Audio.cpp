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

	std::unique_ptr<std::vector<ALCchar*>> System::_devices (nullptr);

	void System::EnumerateDevices() {
		if (!_devices) {
			_devices.reset(new std::vector<ALCchar*>);

			Game::log << "-- Searching for OpenAL devices with ALC:\n";

			ALint major, minor;
			alcGetIntegerv(nullptr, ALC_MAJOR_VERSION, 1, &major);
			alcGetIntegerv(nullptr, ALC_MINOR_VERSION, 1, &minor);
			Game::log << "\tALC version: " << major << "." << minor << "\n";

			Game::log << "\t+ Devices:";

			if (alcIsExtensionPresent(nullptr, "ALC_enumeration_EXT") == ALC_TRUE) {
				const ALCchar *devices = nullptr;

				int i = 1;
				if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT") == ALC_TRUE) {
					devices = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);

					auto device = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
					Game::log << "\n\t\t- (" << i++ << ") " << device << " (default)";
					_devices->push_back((ALCchar*)device);
				} else {
					devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
				}

				while (devices && devices[0] != (char)0x00) {
					Game::log << "\n\t\t- (" << i++ << ") " << devices;

					_devices->push_back((ALCchar*)devices);

					devices += strlen(devices) + 1;
				}
			}

			Game::log << std::endl;
		}
	}

	System::System ( unsigned int index ):
	Util::System ( "Audio" ) {
		/*if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {

		}*/
		
		EnumerateDevices();

		ALCchar *deviceName = nullptr;

		if (_devices->size()) {
			deviceName = _devices->at(index);
		}

		Game::log << "-- Opening OpenAL device '" << deviceName << "'." << std::endl;

		_device = alcOpenDevice(deviceName);
		
		if(!_device) {
			throw false;
		}

		_context = alcCreateContext(_device, 0);
		if (!_context) {
			throw false;
		}
		
		alcMakeContextCurrent(_context);
		
		{
			if(!deviceName || true) {
				deviceName = (char*)alcGetString(_device, ALC_DEVICE_SPECIFIER);
			}

			Game::log << "-- OpenAL context created on device '" << deviceName << "':\n";
			Game::log << "\t" << alGetString(AL_VENDOR) << "(" << alGetString(AL_RENDERER) << ", " << alGetString(AL_VERSION) << ")\n";
			
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
