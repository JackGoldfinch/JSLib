//
//  System.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 07.06.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "System.hpp"

#include "../Game.hpp"

namespace JSLib {
namespace Util {
	
	System::System ( const char *name ):
	_name ( name ) {
		Game::log << "System: Starting <" << _name << ">..." << std::endl;
	}
	
	System::~System() {
		Game::log << "System: Stopping <" << _name << ">... OK. (+" << _stopWatch() << ")" << std::endl;
	}
	
	void System::started() {
		Game::log << "System: Starting <" << _name << ">... OK. (+" << _stopWatch() << ")" << std::endl;
	}
	
	void System::stopping() {
		Game::log << "System: Stopping <" << _name << ">..." << std::endl;
	}
	
}
}
