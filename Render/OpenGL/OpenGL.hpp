//
//  OpenGL.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 24.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_OPENGL_OPENGL_HPP
#define __JSLIB_RENDER_OPENGL_OPENGL_HPP

#include "../../JSLib_Export.hpp"

#include <glbinding/gl33ext/gl.h>
using namespace gl;

#include "../../JSLib_GLM.hpp"

#include <string>

#include <boost/mpl/contains.hpp>

namespace JSLib {
namespace Render {
	
	/**
	 @warning	As the classes and methods in this namespace rely heavily on the OpenGL
				API they are NOT threadsafe and should be used on the main thread ONLY.
	 */
	
namespace OpenGL {
	
	struct JSLIB_EXPORT Exception : public std::runtime_error {
		Exception() : std::runtime_error("Something bad happened within OpenGL.") {}
		Exception ( const std::string text ) : std::runtime_error ( text.c_str() ) {}
		
		virtual ~Exception(){}
	};
	
	template <typename T>
	typename std::enable_if<boost::mpl::contains<glm::VectorTypes, T>::value, GLenum>::type JSLIB_EXPORT glType() {
		GLenum value = GL_NONE;
		
		if ( boost::mpl::contains<glm::IntVectorTypes, T>::value ) {
			value = GL_INT;
		} else if ( boost::mpl::contains<glm::FloatVectorTypes, T>::value ) {
			value = GL_FLOAT;
		} else if ( boost::mpl::contains<glm::DoubleVectorTypes, T>::value ) {
			value = GL_DOUBLE;
		}
		
		return value;
	}
	
	template <typename T>
	typename std::enable_if<boost::mpl::contains<glm::VectorTypes, T>::value, GLuint>::type JSLIB_EXPORT glComponentsCount() {
		return ( sizeof ( T ) / sizeof ( typename T::value_type ) );
	}
	
}
}
}

#include "Object.hpp"
#include "IBindable.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "VertexBuffer.hpp"

#endif // #ifndef __JSLIB_RENDER_OPENGL_OPENGL_HPP
