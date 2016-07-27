//
//  IBindable.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 24.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_OPENGL_IBINDABLE_HPP
#define __JSLIB_RENDER_OPENGL_IBINDABLE_HPP

#ifndef __JSLIB_RENDER_OPENGL_OPENGL_HPP
#error Please include OpenGL.hpp instead.
#endif

namespace JSLib {
namespace Render {
namespace OpenGL {
	
	struct JSLIB_EXPORT IBindable {
		virtual bool isBound() const = 0;
		
		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
	
}
}
}

#endif // #ifndef __JSLIB_RENDER_OPENGL_IBINDABLE_HPP
