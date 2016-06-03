/*
 * System.hpp
 *
 *  Created on: 29.05.2016
 *      Author: johannes
 */

#pragma once
#ifndef AUDIO_SYSTEM_HPP_
#define AUDIO_SYSTEM_HPP_

#include "../JSLib_Export.hpp"

#include <AL/al.h>
#include <AL/alc.h>

namespace JSLib {
namespace Audio {

class JSLIB_EXPORT System {
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

#endif /* AUDIO_SYSTEM_HPP_ */
