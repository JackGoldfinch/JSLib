//
//  Animation.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 10.06.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Animation.hpp"

namespace JSLib {
namespace Util {
	
	std::set<Animations*> Animations::_animations;
	std::set<Animations*> Animations::_removeAnimations;
	
	void Animations::Forward() {
		auto now = Clock::now();
		
		for ( auto animation : _animations ) {
			animation->forward ( now );
		}
		
		if ( ! ( _animations.empty() && _removeAnimations.empty() ) ) {
			for ( auto animation : _removeAnimations ) {
				_animations.erase ( animation );
				
				delete animation;
			}
		}
		
		_removeAnimations.clear();
	}
	
}
}
