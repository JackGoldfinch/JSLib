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
	
	namespace detail {
		
		VertexAttribute_t::VertexAttribute_t ( GLuint index ):
		_vao ( VertexArray::_boundVertexArray ),
		_index ( index ) {
			_vao = VertexArray::Bound();
		}
		
		void VertexAttribute_t::enable ( GLint size, GLenum type, GLboolean normalise, GLsizei stride, const void *pointer ) {
			glEnableVertexAttribArray ( _index );
			glVertexAttribPointer(_index, size, type, normalise, stride, pointer );
		}
		
		void VertexAttribute_t::disable() {
			glDisableVertexAttribArray ( _index );
		}
		
	}
	
	VertexArray *VertexArray::_boundVertexArray = nullptr;
	
	VertexArray *VertexArray::Bound() {
		return _boundVertexArray;
	}
	
	void VertexArray::UnbindAll() {
		glBindVertexArray ( 0 );
		_boundVertexArray = nullptr;
	}
	
	VertexArray::VertexArray() {
		glGenVertexArrays ( 1, &_id );
		
		bind();
	}
	
	VertexArray::~VertexArray() {
		bind();
		
		auto size = _vertexAttributes.size();
		for ( auto i = size - 1; size > i; --i ) {
			auto va = _vertexAttributes[i];
			
			delete va;
		}
		
		unbind();
		
		glDeleteVertexArrays ( 1, &_id );
	}
	
}
}
}
