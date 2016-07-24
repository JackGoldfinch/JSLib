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

#if defined __JSLIB_OPENGL_3_3

#include <glbinding/gl33ext/gl.h>

#elif defined __JSLIB_OPENGL_4_1

#elif defined __JSLIB_OPENGL_4_5

#else

#pragma warning ("No OpenGL Version selected!")

#endif // #ifdef __JSLIB_OPENGL_3_3

using namespace gl;

#include "../../JSLib_GLM.hpp"

#include <string>

#include <boost/mpl/contains.hpp>

namespace JSLib {
namespace Render {
namespace OpenGL {
	
	struct Exception : public std::runtime_error {
		Exception() : std::runtime_error("Something bad happened within OpenGL.") {}
		Exception ( const std::string text ) : std::runtime_error ( text.c_str() ) {}
		
		virtual ~Exception(){}
	};
	
	template <typename T>
	typename std::enable_if<boost::mpl::contains<glm::VectorTypes, T>::value, GLenum>::type glType() {
		GLenum value = GL_NONE;
		
		if ( boost::mpl::contains<glm::IntTypes, T>::value ) {
			value = GL_INT;
		} else if ( boost::mpl::contains<glm::FloatTypes, T>::value ) {
			value = GL_FLOAT;
		} else if ( boost::mpl::contains<glm::DoubleTypes, T>::value ) {
			value = GL_DOUBLE;
		}
		
		return value;
	}
	
}
}
}

#endif // #ifndef __JSLIB_RENDER_OPENGL_OPENGL_HPP
