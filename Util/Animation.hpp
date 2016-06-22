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
#include <memory>

glm::vec2 operator* ( const glm::vec2 &vec, const double scalar );
glm::vec3 operator* ( const glm::vec3 &vec, const double scalar );
glm::vec4 operator* ( const glm::vec4 &vec, const double scalar );

glm::dvec2 operator* ( const glm::dvec2 &vec, const double scalar );
glm::dvec3 operator* ( const glm::dvec3 &vec, const double scalar );
glm::dvec4 operator* ( const glm::dvec4 &vec, const double scalar );

namespace JSLib {
namespace Util {
	
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::time_point<Clock> TimePoint;
	typedef std::chrono::milliseconds Duration;
	
	class Animatables {
	protected:
		static std::set<Animatables*> _animatables;
		static std::set<Animatables*> _finishedAnimatables;
		
		virtual void progress ( const TimePoint &now ) = 0;
		virtual void cleanup() = 0;
		
	public:
		static void Progress();
		
		virtual ~Animatables(){}
	};
	
	template <typename T>
	class Animatable : public Animatables {
		typedef T ValueType;
		
	protected:
		class Animation {
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
			
			void progress ( const TimePoint &now ) {
				auto deltaTime = std::chrono::duration_cast<Duration>(now - _startTimePoint);
				
				auto completion = (double)deltaTime.count() / _duration.count();
				completion = glm::min ( completion, 1.0 );
				
				_animatable._value = _startValue + ( _delta * completion );
				
				if ( completion >= 1.f ) {
					_finishedAnimatables.insert ( &_animatable );
				}
			}
		};
		
		ValueType _value;
		
		std::unique_ptr<Animation> _animation;
		
	public:
		Animatable(){}
		
		Animatable ( const ValueType &value ):
		_value ( value ) {}
		
		template <typename ... Args>
		Animatable ( Args ... args ) {}
		
		void animate ( const ValueType &target, const Duration duration ) {
			_animation.reset ( new Animation ( *this, target, duration ) );
			
			Animatables::_animatables.insert ( this );
		}
		
		virtual void progress ( const TimePoint &now ) {
			if ( _animation ) {
				_animation->progress ( now );
			}
		}
		
		virtual void cleanup() {
			_animatables.erase ( this );
			
			_animation.reset();
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
		
		ValueType operator*() const {
			return _value;
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
	
	std::ostream &operator<< ( std::ostream &stream, const Advec3 &vec );
	
}

#endif // #ifdef __JSLIB_ANIMATION_HPP
