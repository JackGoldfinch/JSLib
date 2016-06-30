//
//  JSLib_GLM.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 30.05.2016.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_GLM_HPP
#define __JSLIB_GLM_HPP

#ifdef __JSLIB

#define GLM_MESSAGES

#define GLM_SWIZZLE
#define GLM_FORCE_SIZE_T_LENGTH

#endif // #ifdef __JSLIB

#if (defined JSLIB_GLM_FWD) || (! defined JSLIB_GLM_NO_FWD)

#include <glm/fwd.hpp>

#else

#include <glm/glm.hpp>

#endif

namespace glm {
	
	typedef vec3 color3;
	typedef vec4 color4;
	
} // namespace glm

#endif /* __JSLIB_GLM_HPP */
