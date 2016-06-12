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
	
	std::set<Animatables*> Animatables::_animatables;
	std::set<Animatables*> Animatables::_finishedAnimatables;
	
	void Animatables::Progress() {
		auto now = Clock::now();
		
		for ( auto animatable : _animatables ) {
			animatable->progress ( now );
		}
		
		for ( auto animatable : _finishedAnimatables ) {
			animatable->cleanup();
		}
		
		_finishedAnimatables.clear();
	}
	
}
	
	std::ostream &operator<< ( std::ostream &stream, const Advec3 &vec ) {
		const auto &v = *vec;
		stream << "dvec3: r" << v.r << " g" << v.g << " b" << v.b;
		
		return stream;
	}
	
}
