//
//  Buffer.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 24.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_OPENGL_BUFFER_HPP
#define __JSLIB_RENDER_OPENGL_BUFFER_HPP

#ifndef __JSLIB_RENDER_OPENGL_OPENGL_HPP
#error Please include OpenGL.hpp instead.
#endif

#include <map>

namespace JSLib {
namespace Render {
namespace OpenGL {
	
	class JSLIB_EXPORT Buffer : public Object, public IBindable {
	public:
		typedef std::map<GLenum, Buffer*> BufferMap;
		
	protected:
		static BufferMap _boundBuffers;
		
		GLenum _target;
		
	public:
		static Buffer* Bound ( GLenum target );
		static bool IsBound ( const Buffer *buffer ) {
			return buffer == Bound ( buffer->_target );
		}
		
		static void Bind ( GLenum target, Buffer *buffer );
		static void Bind ( Buffer *buffer ) {
			if ( buffer ) {
				Bind ( buffer->_target, buffer );
			}
		}
		static void Unbind ( GLenum target ) {
			Bind ( target, nullptr );
		}
		static void Unbind ( const Buffer *buffer ) {
			if ( buffer && IsBound ( buffer ) ) {
				Unbind ( buffer->_target );
			}
		}
		
		/**
		 * @param target GLenum describing the binding point of the buffer
		 * @param data Pointer to data
		 * @param size Length of data
		 * @param usage Glenum describing the usage hint of the buffer
		 *
		 * @throws std::invalid_argument
		 */
		
		Buffer ( GLenum target, const GLvoid *data, GLsizei size, GLenum usage = GL_STATIC_DRAW );
		virtual ~Buffer();
		
		void setData ( const GLvoid *data, GLsizei size, GLenum usage = GL_STATIC_DRAW );
		void updateData ( const GLvoid *data, GLsizei size );
		
		virtual bool isBound() const {
			return IsBound ( this );
		}
		
		virtual void bind() {
			Bind ( this );
		}
		
		virtual void unbind() {
			Unbind ( this );
		}
		
	};
	
}
}
}

#endif // #ifndef __JSLIB_RENDER_OPENGL_BUFFER_HPP
