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
	
	Quad::Quad():
	_vbo ( _data, 4 * sizeof ( glm::vec2 ) ) {
		_vao.vertexAttribute<glm::vec2>(); // index 0
	}
	
	void Quad::render() {
		_vao.bind();
		
		glDrawArrays ( GL_TRIANGLE_STRIP, 0, 4 );
	}
	
}
}
