//
//  Audio.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 29.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef AUDIO_AUDIO_HPP_
#define AUDIO_AUDIO_HPP_

#include "../JSLib_Export.hpp"

#include "../JSLib_OpenAL.hpp"

#include "../Util/System.hpp"

namespace JSLib {
namespace Audio {

	class JSLIB_EXPORT System : public Util::System {
	protected:
		ALCdevice *_device;
		ALCcontext *_context;

	public:
		System();
		~System();
	};

} /* namespace Audio */

	typedef Audio::System AudioSystem;

} /* namespace JSLib */

#endif /* AUDIO_AUDIO_HPP_ */
