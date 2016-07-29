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

namespace JSLib {
namespace Render {
namespace OpenGL {
	
	template <GLenum target>
	class JSLIB_EXPORT Buffer : public Object, public IBindable {
		friend VertexArray;
		
	public:
		struct MappingInfo {
			Buffer *mappedBuffer;
			void *mappedData;
		};
	
	protected:
		static Buffer *_boundBuffer;
		static MappingInfo _mappingInfo;
		
	public:
		static Buffer *Bound() {
			return _boundBuffer;
		}
		
		static void UnbindAll() {
			glBindBuffer ( target, 0 );
			_boundBuffer = nullptr;
		}
		
		Buffer ( const GLvoid *data, GLsizei size ) {
			glGenBuffers ( 1, &_id );
			
			bind();
			
			setData ( data, size );
		}
		
		virtual ~Buffer() {
			unbind();
			
			glDeleteBuffers ( 1, &_id );
		}
		
		virtual bool isBound() const {
			return this == _boundBuffer;
		}
		
		virtual void bind() {
			if ( this == _boundBuffer ) {
				return;
			}
			
			if ( ! VertexArray::_boundVertexArray ) {
				throw false;
			}
			
			glBindBuffer ( target, _id );
			_boundBuffer = this;
		}
		
		virtual void unbind() {
			if ( this != _boundBuffer ) {
				return;
			}
			
			glBindBuffer ( target, 0 );
			_boundBuffer = nullptr;
		}
		
		void setData ( const GLvoid *data, GLsizei size, GLenum usage = GL_STATIC_DRAW ) {
			bind();
			
			glBufferData ( target, size, data, usage );
		}
		
		void *map ( GLenum access = GL_READ_ONLY ) {
			if ( ! _mappingInfo.mappedData ) {
				_mappingInfo.mappedData = glMapBuffer ( target, access );
				
				if ( _mappingInfo.mappedData ) {
					_mappingInfo.mappedBuffer = this;
				}
			}
			
			if ( _mappingInfo.mappedBuffer == this ) {
				return _mappingInfo.mappedData;
			} else {
				return nullptr;
			}
		}
		
		GLboolean unmap() {
			GLboolean ret = GL_FALSE;
			
			if ( _mappingInfo.mappedData && _mappingInfo.mappedBuffer == this ) {
				ret = glUnmapBuffer ( target );
				
				if ( ret ) {
					_mappingInfo = {
						nullptr, nullptr
					};
				}
			}
			
			return ret;
		}
		
		void updateData ( const GLvoid *data, GLsizei size ) {
			bind();
			
			auto ptr = map ( GL_WRITE_ONLY );
			memcpy ( ptr, data, size );
			unmap();
		}
	};
	
	template <GLenum target>
	Buffer<target> *Buffer<target>::_boundBuffer = nullptr;
	
	template <GLenum target>
	typename Buffer<target>::MappingInfo Buffer<target>::_mappingInfo = {
		nullptr, nullptr
	};
	
}
}
}

#endif // #ifndef __JSLIB_RENDER_OPENGL_BUFFER_HPP
