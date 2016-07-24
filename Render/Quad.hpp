//
//  Quad.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 08.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_QUAD_HPP
#define __JSLIB_RENDER_QUAD_HPP

#include "../JSLib_Export.hpp"

#include "../JSLib_OpenGL.hpp"

#include <glm/glm.hpp>

namespace JSLib {
namespace Render {
	
	class JSLIB_EXPORT Quad {
	protected:
		static const glm::vec2 _data[];
		
		GLuint _vao, _vbo;
		
	public:
		Quad();
		~Quad();
		
		void render();
	};
	
}
}

#endif // #ifndef __JSLIB_RENDER_QUAD_HPP
