//
//  VertexArray.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 25.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "OpenGL.hpp"

namespace JSLib {
namespace Render {
namespace OpenGL {
	
	VertexArray *VertexArray::_boundVertexArray = nullptr;
	
	VertexArray *VertexArray::Bound() {
		return _boundVertexArray;
	}
	
	bool VertexArray::IsBound ( const VertexArray *vertexArray ) {
		return _boundVertexArray == vertexArray;
	}
	
	void VertexArray::Bind ( VertexArray *vertexArray ) {
		if ( _boundVertexArray != vertexArray ) {
			_boundVertexArray = vertexArray;
			
			glBindVertexArray ( _boundVertexArray ? _boundVertexArray->_id : 0 );
		}
	}
	
	VertexArray::VertexArray() {
		glGenVertexArrays ( 1, &_id );
		
		bind();
	}
	
	VertexArray::~VertexArray() {
		unbind();
		
		glDeleteVertexArrays ( 1, &_id );
	}
	
}
}
}
