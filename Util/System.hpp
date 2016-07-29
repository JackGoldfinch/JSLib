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
	
	/**
		@brief This class provides helper functionality for logging purposes.
	 */
	
	class JSLIB_EXPORT System {
	protected:
		const char *_name;
		
		StopWatch _stopWatch;
		
	public:
		System ( const char *name );
		virtual ~System();
		
		/**
			@brief Log: System did start.
			@discussion Call this function to signal the completion of the system start.
		 */
		
		void started();
		
		/**
			@brief Log: System will stop.
			@discussion Call this function to signal the beginning of the system stop.
		 */
		
		void stopping();
	};
	
}
}

#endif // #ifndef __JSLIB_UTIL_SYSTEM_HPP
