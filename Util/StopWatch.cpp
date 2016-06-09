//
//  StopWatch.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.06.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "StopWatch.hpp"

namespace JSLib {
namespace Util {
	
	StopWatch::StopWatch():
	_start (pt::microsec_clock::local_time()) {
		
	}
	
}
}
