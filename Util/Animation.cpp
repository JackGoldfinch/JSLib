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
	
	std::set<IAnimatable*> IAnimatable::_animatables;
	std::set<IAnimatable*> IAnimatable::_finishedAnimatables;
	
	void IAnimatable::Process() {
		auto now = Clock::now();
		
		/*
		Avec3 ani;
		ani.animate ( 2 );
		*/
		
		for ( auto animatable : _animatables ) {
			animatable->process ( now );
		}
		
		for ( auto animatable : _finishedAnimatables ) {
			animatable->cleanup();
		}
		
		_finishedAnimatables.clear();
	}
	
	template <> template <>
	Animatable<glm::dvec2>::Animatable ( GLdouble x, GLdouble y ) {
		_value = { x, y };
	}

	template <> template <>
	Animatable<glm::dvec3>::Animatable ( GLdouble x, GLdouble y, GLdouble z ) {
		_value = { x, y, z };
	}

	template <> template <>
	Animatable<glm::dvec4>::Animatable ( GLdouble x, GLdouble y, GLdouble z, GLdouble w ) {
		_value = { x, y, z, w };
	}

	template <> template <>
	Animatable<glm::vec2>::Animatable ( GLfloat x, GLfloat y ) {
		_value = { x, y };
	}

	template <> template <>
	Animatable<glm::vec3>::Animatable ( GLfloat x, GLfloat y, GLfloat z ) {
		_value = { x, y, z };
	}

	template <> template <>
	Animatable<glm::vec4>::Animatable ( GLfloat x, GLfloat y, GLfloat z, GLfloat w ) {
		_value = { x, y, z, w };
	}
}
}
