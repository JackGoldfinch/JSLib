//
//  JSLib_OpenAL.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 03.06.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_OPENAL_HPP
#define __JSLIB_OPENAL_HPP

#ifdef __APPLE__

#include <OpenAL/OpenAL.h>

#else

#include <AL/al.h>
#include <AL/alc.h>

#endif // #ifdef __APPLE

#endif // #ifndef __JSLIB_OPENAL_HPP
