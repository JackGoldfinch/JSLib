//
//  StopWatch.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.06.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_UTIL_STOPWATCH_HPP
#define __JSLIB_UTIL_STOPWATCH_HPP

#include "../JSLib_Export.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
namespace pt = boost::posix_time;

namespace JSLib {
namespace Util {
	
	class JSLIB_EXPORT StopWatch {
	protected:
		pt::ptime _start;
		
	public:
		StopWatch();
		
		pt::time_duration operator() () {
			return pt::microsec_clock::local_time() - _start;
		}
	};
	
}
}

#endif // #ifndef __JSLIB_UTIL_STOPWATCH_HPP
