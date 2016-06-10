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

#include "../JSLib_GLM.hpp"

#include <chrono>

namespace JSLib {
namespace Util {
	
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::time_point<Clock> TimePoint;
	typedef std::chrono::milliseconds Duration;
	
	template <class T>
	class Animatable {
		typedef T ValueType;
		
	protected:
		class Animation {
		protected:
			Animatable<ValueType> &_animatable;
			
			ValueType _targetValue;
			TimePoint _targetTimePoint;
			
		public:
			Animation ( Animatable &animatable, ValueType && targetValue, Duration &&duration ):
			_animatable ( animatable ) {
				_targetValue = targetValue;
				_targetTimePoint = Clock::now() + duration;
			}
		};
		
		ValueType _value;
		
	public:
		operator ValueType() {
			return _value;
		}
		
		Animatable &operator= ( const ValueType& value ) {
			_value = value;
			
			return *this;
		}
		
		ValueType operator+ ( const ValueType &value ) {
			return _value + value;;
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
	
	void test();

}
}

#endif // #ifdef __JSLIB_ANIMATION_HPP
