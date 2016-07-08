//
//  Quad.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 08.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Quad.hpp"

namespace JSLib {
namespace Render {
	
	const GLfloat _data[] = {
		
	};
	
	Quad::Quad() {
		glGenVertexArrays ( 1, &_vao );
		glBindVertexArray ( _vao );
		
		glGenBuffers ( 1, &_vbo );
		glBindBuffer (GL_ARRAY_BUFFER, _vao );
		
		glBufferData ( GL_ARRAY_BUFFER, 4, _data, GL_STATIC_DRAW );
	}
	
	Quad::~Quad() {
		glDeleteBuffers ( 1, &_vbo );
		
		glDeleteVertexArrays ( 1, &_vao );
	}
	
	void Quad::render() {
		glBindVertexArray ( _vao );
		
		glDrawArrays ( GL_TRIANGLE_STRIP, 0, 4 );
	}
	
}
}
