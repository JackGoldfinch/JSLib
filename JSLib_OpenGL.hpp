//
//  JSLib_OpenGL.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_OPENGL_HPP
#define __JSLIB_OPENGL_HPP

#if defined __JSLIB_OPENGL_3_3

#include <glbinding/gl33ext/gl.h>

#elif defined __JSLIB_OPENGL_4_1

#elif defined __JSLIB_OPENGL_4_5

#else

#pragma warning ("No OpenGL Version selected!")

#endif // #ifdef __JSLIB_OPENGL_3_3

using namespace gl;

#include <string>

struct OpenGLException : public std::runtime_error {
	OpenGLException() : std::runtime_error("Something bad happened within OpenGL.") {}
	OpenGLException ( const std::string text ) : std::runtime_error ( text.c_str() ) {}
	
	virtual ~OpenGLException(){}
};

#endif // #ifndef __JSLIB_OPENGL_HPP
