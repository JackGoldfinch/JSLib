//
//  Audio.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 29.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_AUDIO_AUDIO_HPP
#define __JSLIB_AUDIO_AUDIO_HPP

#include "../JSLib_Export.hpp"

#include "../JSLib_OpenAL.hpp"

#include "../Util/System.hpp"

namespace JSLib {
namespace Audio {

	class JSLIB_EXPORT System : public Util::System {
	protected:
		static std::unique_ptr<std::vector<ALCchar*>> _devices;

		static void EnumerateDevices();

		ALCdevice *_device;
		ALCcontext *_context;

	public:
		System ( unsigned int index = 0 );
		~System();
	};

} /* namespace Audio */

	typedef Audio::System AudioSystem;

} /* namespace JSLib */

#endif // #ifndef __JSLIB_AUDIO_AUDIO_HPP
