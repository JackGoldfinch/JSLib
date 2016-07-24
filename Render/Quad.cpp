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
	
	const glm::vec2 Quad::_data[] = {
		{ -0.5f,  0.5f },
		{ -0.5f, -0.5f },
		{  0.5f,  0.5f },
		{  0.5f, -0.5f }
	};
	
	Quad::Quad() {
		glGenVertexArrays ( 1, &_vao );
		glBindVertexArray ( _vao );
		
		glGenBuffers ( 1, &_vbo );
		glBindBuffer (GL_ARRAY_BUFFER, _vbo );
		
		glBufferData ( GL_ARRAY_BUFFER, 4 * sizeof ( glm::vec3 ), _data, GL_STATIC_DRAW );
		
		glEnableVertexAttribArray ( 0 );
		glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, sizeof ( glm::vec3 ), ( void* ) offsetof(glm::vec3, x) );
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
