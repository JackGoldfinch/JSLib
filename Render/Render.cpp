//
//  Render.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSL_RENDER_RENDER_CPP

#include "Render.hpp"

#include "../Game.hpp"

namespace JSLib {
namespace Render {
	
	System::System ( Window *window ):
	Util::System ( "Render" ),
	_window ( window ) {
		started();
	}
	
	System::~System() {
		stopping();
	}
	
	void System::process() {
		
	}
	
} // namespace Render
} // namespace JSLib
