//
//  Object.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 24.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_OPENGL_OBJECT_HPP
#define __JSLIB_RENDER_OPENGL_OBJECT_HPP

#ifndef __JSLIB_RENDER_OPENGL_OPENGL_HPP
#error Please include OpenGL.hpp instead.
#endif

namespace JSLib {
namespace Render {
namespace OpenGL {
	
	class JSLIB_EXPORT Object {
	protected:
		GLuint _id;
		
	public:
		Object();
		virtual ~Object();
	};
	
}
}
}

#endif // #ifndef __JSLIB_RENDER_OPENGL_OBJECT_HPP
