//
//  VertexArray.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 25.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_OPENGL_VERTEXARRAY_HPP
#define __JSLIB_RENDER_OPENGL_VERTEXARRAY_HPP

#include <vector>

namespace JSLib {
namespace Render {
namespace OpenGL {
	
	class VertexArray;
	
	namespace detail {
		
		class JSLIB_EXPORT VertexAttribute_t {
		protected:
			VertexArray *_vao;
			GLuint _index;
			
			VertexAttribute_t ( GLuint index );
			
		public:
			virtual ~VertexAttribute_t(){}
			
			void enable ( GLint size, GLenum type, GLboolean normalise, GLsizei stride, const void *pointer );
			void disable();
		};
		
	}
	
	template <typename V>
	class JSLIB_EXPORT VertexAttribute : public detail::VertexAttribute_t {
		friend VertexArray;
		
	protected:
		VertexAttribute ( GLuint index, GLboolean normalise, GLsizei stride, const void *pointer ):
		VertexAttribute_t ( index ) {
			if ( ! pointer ) {
				if ( boost::mpl::contains<glm::VectorTypes, V>::value ) {
					pointer = ( void* ) offsetof ( V, x );
				}
			}
			
			enable ( glComponentsCount<V>(), glType<V>(), normalise, stride, pointer );
		}
		
	public:
		virtual ~VertexAttribute() {
			disable();
		}
	};
	
	class JSLIB_EXPORT VertexArray : public Object, public IBindable {
		friend detail::VertexAttribute_t;
		template <GLenum target> friend class Buffer;
		
	protected:
		static VertexArray *_boundVertexArray;
		
		std::vector<detail::VertexAttribute_t*> _vertexAttributes;
		
	public:
		static VertexArray *Bound();
		
		static void UnbindAll();
		
		VertexArray();
		virtual ~VertexArray();
		
		template <typename V>
		typename std::enable_if<boost::mpl::contains<glm::VectorTypes, V>::value, void>::type
		vertexAttribute ( GLboolean normalise = GL_FALSE, GLsizei stride = 0, const void *pointer = nullptr ) {
			bind();
			
			auto index = _vertexAttributes.size();
			_vertexAttributes.push_back ( new VertexAttribute<V> ( ( GLuint ) index, normalise, stride, pointer ) );
		}
		
		virtual bool isBound() const {
			return this == _boundVertexArray;
		}
		
		virtual void bind() {
			if ( this == _boundVertexArray ) {
				return;
			}
			
			glBindVertexArray ( _id );
			_boundVertexArray = this;
		}
		
		virtual void unbind() {
			if ( this != _boundVertexArray ) {
				return;
			}
			
			glBindVertexArray ( 0 );
			_boundVertexArray = nullptr;
		}
		
	};
	
}
}
}

#endif // #ifndef __JSLIB_RENDER_OPENGL_VERTEXARRAY_HPP
