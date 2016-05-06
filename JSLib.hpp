/*
 *  JSLib.hpp
 *  JSLib
 *
 *  Created by Johannes Stieglitz on 06.05.16.
 *  Copyright © 2016 Johannes Stieglitz. All rights reserved.
 *
 */

#pragma once
#ifndef __JSLIB_HPP
#define __JSLIB_HPP

#include "JSLib_Export.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

class JSLIB_EXPORT JSLib
{
	public:
		void HelloWorld(const char *);
};

#pragma GCC visibility pop

#endif // #ifndef __JSLIB_HPP
