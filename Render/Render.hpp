//
//  Render.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_RENDER_HPP
#define __JSLIB_RENDER_RENDER_HPP

#include "../JSLib_Export.hpp"

#include "../Util/System.hpp"

namespace JSLib {
	
	class Window;
	
namespace Render {
	
	class JSLIB_EXPORT System : public Util::System {
	protected:
		Window *_window;
		
	public:
		System ( Window *window );
		~System();
		
		virtual void process();
	};
	
} // namespace Render

typedef Render::System RenderSystem;
	
} // namespace JSLib

#endif // #ifndef __JSLIB_RENDER_RENDER_HPP

