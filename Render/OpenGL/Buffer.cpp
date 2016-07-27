//
//  Buffer.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 24.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "OpenGL.hpp"

namespace JSLib {
namespace Render {
namespace OpenGL {
	
	Buffer::BufferMap Buffer::_boundBuffers;
	
	Buffer *Buffer::Bound ( GLenum target ) {
		return _boundBuffers[target];
	}
	
	void Buffer::Bind ( GLenum target, Buffer *buffer ) {
		if ( buffer != _boundBuffers[target] ) {
			_boundBuffers[target] = buffer;
			
			glBindBuffer ( target, buffer ? buffer->_id : 0 );
		}
	}
	
	Buffer::Buffer ( GLenum target, const GLvoid *data, GLsizei size, GLenum usage ):
	_target ( target ) {
		if ( ( ! data ) || ( size == 0 ) ) {
			throw std::invalid_argument ( "" );
		}
		
		glGenBuffers ( 1, &_id );
		
		setData ( data, size );
	}
	
	Buffer::~Buffer() {
		unbind();
		
		glDeleteBuffers ( 1, &_id );
	}
	
	void Buffer::setData ( const GLvoid *data, GLsizei size, GLenum usage ) {
		bind();
		
		glBufferData ( _target, size, data, usage );
	}
	
	void Buffer::updateData ( const GLvoid *data, GLsizei size ) {
		bind();
		
		GLvoid *ptr = glMapBuffer ( _target, GL_WRITE_ONLY );
		memcpy ( ptr, data, size );
		glUnmapBuffer ( _target );
	}
	
}
}
}
