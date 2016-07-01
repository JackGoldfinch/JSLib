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

#include "../JSLib_GLM.hpp"

#include <chrono>
#include <set>
#include <iostream>
#include <memory>

#include <glm/glm.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/contains.hpp>

typedef boost::mpl::vector<glm::vec2, glm::vec3, glm::vec4, glm::dvec2, glm::dvec3, glm::dvec4> vectors;

namespace JSLib {
	
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::time_point<Clock> TimePoint;
	typedef std::chrono::milliseconds Duration;
	
namespace Util {
	
	class IAnimatable {
	protected:
		static std::set<IAnimatable*> _animatables;
		static std::set<IAnimatable*> _finishedAnimatables;
		
		virtual void process ( const TimePoint &now ) = 0;
		virtual void cleanup() = 0;
		
	public:
		static void Process();
		
		virtual ~IAnimatable(){}
	};
	
	template <typename T>
	class Animatable : public IAnimatable {
		typedef T ValueType;
		
	protected:
		class IAnimation {
		protected:
			Animatable<ValueType> &_animatable;
			
		public:
			IAnimation ( Animatable &animatable ):
			_animatable ( animatable ) {
				//std::cout << "Animation constructed." << std::endl;
			}
			
			virtual ~IAnimation() {
				//std::cout << "Animation destructed." << std::endl;
			}
			
			virtual void process ( const TimePoint &now ) = 0;
		};
		
		class ISimpleAnimation : public IAnimation {
		protected:
			TimePoint _startTimePoint;
			Duration _duration;
			
			ValueType _startValue;
			ValueType _delta;
			
		public:
			ISimpleAnimation ( Animatable &animatable, const ValueType &targetValue, const Duration &duration ):
			IAnimation ( animatable ),
			_startTimePoint ( Clock::now() ),
			_duration ( duration ),
			_startValue ( animatable._value ),
			_delta ( targetValue - animatable._value ) {
				//std::cout << "SimpleAnimation constructed." << std::endl;
			}
			
			virtual ~ISimpleAnimation() {
				//std::cout << "SimpleAnimation destructed." << std::endl;
			}
			
			virtual void process ( const TimePoint &now ) = 0;
		};
		
		class LinearAnimation : public ISimpleAnimation {
		public:
			LinearAnimation ( Animatable &animatable, const ValueType &targetValue, const Duration &duration ):
			ISimpleAnimation ( animatable, targetValue, duration ) {
				//std::cout << "LinearAnimation constructed." << std::endl;
			}
			
			/*
			template<typename U = ValueType>
			LinearAnimation ( typename std::enable_if<boost::mpl::contains<vectors, U>::value, int> test ) {
				
			}
			*/
			
			virtual ~LinearAnimation(){
				//std::cout << "LinearAnimation destructed." << std::endl;
			}
			
			virtual void process ( const TimePoint &now ) {
				auto deltaTime = std::chrono::duration_cast<Duration>(now - this->_startTimePoint);
				
				auto completion = (double)deltaTime.count() / this->_duration.count();
				completion = glm::min ( completion, 1.0 );
				
				this->_animatable._value = this->_startValue + ( this->_delta * completion );
				
				if ( completion >= 1.f ) {
					_finishedAnimatables.insert ( &this->_animatable );
				}
			}
		};
		
		ValueType _value;
		
		mutable bool _hasChanged = false;
		
		std::unique_ptr<IAnimation> _animation;
		
		void change() {
			_hasChanged = true;
		}
		
	public:
		Animatable(){}
		
		Animatable ( const ValueType &value ):
		_value ( value ) {}
		
		template <typename ... Args>
		Animatable ( Args ... args ) {}
		
		void animate ( const ValueType &target, const Duration duration ) {
			_animation.reset ( new LinearAnimation ( *this, target, duration ) );
			
			IAnimatable::_animatables.insert ( this );
		}
		
		void animate ( IAnimation *animation );
		
		template<typename U = ValueType>
		void animate ( typename std::enable_if<boost::mpl::contains<vectors, U>::value, int>::type test ) {
			
		}
		
		virtual void process ( const TimePoint &now ) {
			if ( _animation ) {
				_animation->process ( now );
				
				change();
			}
		}
		
		virtual void cleanup() {
			_animatables.erase ( this );
			
			_animation.reset();
		}
		
		bool hasChanged() const {
			bool changed = _hasChanged;
			
			_hasChanged = false;
			
			return changed;
		}
		
		bool hasAnimation() const {
			return _animation != nullptr;
		}
		
		operator ValueType() {
			return _value;
		}
		
		bool operator== ( const ValueType &value ) {
			return _value == value;
		}
		
		ValueType operator= ( const ValueType &value ) {
			change();
			
			_value = value;
			
			return _value;
		}
		
		ValueType operator+ ( const ValueType &value ) {
			return _value + value;
		}
		
		ValueType operator+= ( const ValueType &value) {
			change();
			
			return _value += value;
		}
		
		ValueType operator- ( const ValueType &value ) {
			return _value - value;
		}
		
		ValueType operator-= ( const ValueType &value) {
			change();
			
			return _value -= value;
		}
		
		ValueType operator*() const {
			return _value;
		}
		
		ValueType *operator->() {
			return &_value;
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
