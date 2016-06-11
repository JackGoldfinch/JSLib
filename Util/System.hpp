//
//  System.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 07.06.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_UTIL_SYSTEM_HPP
#define __JSLIB_UTIL_SYSTEM_HPP

#include "../JSLib_Export.hpp"

#include "StopWatch.hpp"

namespace JSLib {
namespace Util {
	
	class JSLIB_EXPORT System {
	protected:
		const char *_name;
		
		StopWatch _stopWatch;
		
	public:
		System ( const char *name );
		~System();
		
		void started();
		void stopping();
	};
	
}
}

#endif // #ifndef __JSLIB_UTIL_SYSTEM_HPP
