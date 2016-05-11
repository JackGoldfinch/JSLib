//
//  Worker.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Worker.hpp"

namespace JSLib { namespace Util {
	Worker &Worker::Get() {
		static Worker me;
		
		return me;
	}
	
	Worker::Worker() :
	_mainThreadWork(new Work (_mainThread)),
	_bgThreadWork(new Work (_bgThread)) {
		
	}
	
	Worker::~Worker() {
		reset();
	}
	
	std::size_t Worker::runMainThread() {
		return _mainThread.run();
	}
	
	void Worker::reset() {
		_bgThreadWork.reset();
		_mainThreadWork.reset();
	}
}}
