//
//  IRenderable.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 08.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_IRENDERABLE_HPP
#define __JSLIB_RENDER_IRENDERABLE_HPP

#include "../JSLib_Export.hpp"

#include <set>
#include <type_traits>

namespace JSLib {
namespace Render {
	
	class JSLIB_EXPORT IRenderable {
	public:
		typedef std::set<IRenderable*> Set;
		
	protected:
		static Set _renderables;
		
		IRenderable();
		
	public:
		static void Render();
		
		/*
		template <typename T, typename ...Args>
		static typename std::enable_if<std::is_base_of<IRenderable, T>::value, IRenderable*>::type Create ( Args ...args ) {
			auto pointer = new T ( args... );
			
			_renderables.insert ( Unique ( pointer ) );
			
			return pointer;
		}
		*/
		
		virtual ~IRenderable();
		
		virtual void render() = 0;
		
		void *operator new ( std::size_t n );
		void operator delete (void *p, std::size_t n );
	};
	
}
}

#endif // #ifndef __JSLIB_RENDER_IRENDERABLE_HPP
