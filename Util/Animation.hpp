//
//  Animation.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 10.06.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_ANIMATION_HPP
#define __JSLIB_ANIMATION_HPP

#include <glbinding/gl/types.h>
using namespace gl;

#define JSLIB_GLM_NO_FWD

#include "../JSLib_GLM.hpp"

#include <chrono>
#include <set>
#include <iostream>

namespace JSLib {
namespace Util {
	
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::time_point<Clock> TimePoint;
	typedef std::chrono::milliseconds Duration;
	
	class Animations {
		template <class T> friend class Animatable;
		
	protected:
		static std::set<Animations*> _animations;
		static std::set<Animations*> _removeAnimations;
		
		virtual void forward ( const TimePoint &now) = 0;
		
	public:
		virtual ~Animations(){}
		
		static void Forward();
	};
	
	template <class T>
	class Animatable {
		typedef T ValueType;
		
	protected:
		class Animation : public Animations {
		protected:
			Animatable<ValueType> &_animatable;
			
			TimePoint _startTimePoint;
			Duration _duration;
			
			ValueType _startValue;
			ValueType _delta;
			
		public:
			Animation ( Animatable &animatable, const ValueType &targetValue, const Duration &duration ):
			_animatable ( animatable ),
			_startTimePoint ( Clock::now() ),
			_duration ( duration ),
			_startValue ( _animatable._value ),
			_delta ( targetValue - _animatable._value ){
				//std::cout << "Animation constructed." << std::endl;
			}
			
			~Animation(){
				//std::cout << "Animation destructed." << std::endl;
			}
			
			virtual void forward ( const TimePoint &now ) {
				auto deltaTime = std::chrono::duration_cast<Duration>(now - _startTimePoint);
				
				auto completion = (double)deltaTime.count() / _duration.count();
				completion = glm::min ( completion, 1.0 );
				
				_animatable._value = _startValue + ( _delta * completion );
				
				if ( completion >= 1.f ) {
					Animations::_removeAnimations.insert ( this );
				}
			}
		};
		
		ValueType _value;
		
	public:
		Animatable(){}
		
		Animatable ( const ValueType &value ):
		_value ( value ) {}
		
		void animate ( const ValueType &target, const Duration duration ) {
			Animations::_animations.insert ( new Animation ( *this, target, duration ) );
		}
		
		operator ValueType() {
			return _value;
		}
		
		bool operator== ( const ValueType &value ) {
			return _value == value;
		}
		
		ValueType operator= ( const ValueType &value ) {
			_value = value;
			
			return _value;
		}
		
		ValueType operator+ ( const ValueType &value ) {
			return _value + value;
		}
		
		ValueType operator+= ( const ValueType &value) {
			return _value += value;
		}
		
		ValueType operator- ( const ValueType &value ) {
			return _value - value;
		}
		
		ValueType operator-= ( const ValueType &value) {
			return _value -= value;
		}
	};
	
}
	
	typedef Util::Animatable<GLuint> Auint;
	typedef Util::Animatable<GLint> Aint;
	
	typedef Util::Animatable<GLfloat> Afloat;
	typedef Util::Animatable<GLdouble> Adouble;
	
	typedef Util::Animatable<glm::vec2> Avec2;
	typedef Util::Animatable<glm::vec3> Avec3;
	typedef Util::Animatable<glm::vec4> Avec4;
	
	typedef Util::Animatable<glm::dvec2> Advec2;
	typedef Util::Animatable<glm::dvec3> Advec3;
	typedef Util::Animatable<glm::dvec4> Advec4;
	
}

#endif // #ifdef __JSLIB_ANIMATION_HPP
