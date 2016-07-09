//
//  Shader.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 08.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Shader.hpp"

#include <vector>

namespace JSLib {
namespace Render {
	
	const int numShaders = 3;
	
	void createShader ( GLuint &p, GLuint &sh, GLenum type, const char *source ) {
		sh = glCreateShader ( type );
		
		if ( !sh ) {
			throw OpenGLException();
		}
		
		glShaderSource ( sh, 1, &source, nullptr );
		
		glCompileShader ( sh );
		
		GLint length;
		std::string infoLog;
		glGetShaderiv ( sh, GL_INFO_LOG_LENGTH, &length );
		if ( length ) {
			std::vector<GLchar> buf ( length );
			
			glGetShaderInfoLog ( sh, length, nullptr, &buf[0] );
			
			infoLog = &buf[0];
		}
		
		GLboolean status;
		glGetShaderiv ( sh, GL_COMPILE_STATUS, &status );
		if ( status != GL_TRUE ) {
			glDeleteShader ( sh );
			sh = 0;
			
			throw Shader::CompilationException ( infoLog );
		}
		
		glAttachShader ( p, sh );
	}
	
	void detachShaders ( const GLuint &p, GLuint *sh ) {
		for ( GLuint i = 0; i < numShaders; ++i ) {
			glDetachShader ( p, sh[i] );
		}
	}
	
	void deleteShaders ( GLuint *sh ) {
		for ( GLuint i = 0; i < numShaders; ++i ) {
			glDeleteShader ( sh[i] );
		}
	}
	
	Shader::Shader ( const char *srcVS, const char *srcFS, const char *srcGS ) {
		if ( ! ( srcVS && srcFS ) ) {
			throw IncompleteException();
		}
		
		_id = glCreateProgram();
		
		if ( !_id ) {
			throw OpenGLException();
		}
		
		GLuint sh[numShaders];
		std::memset ( sh, 0, numShaders * sizeof ( GLuint ) );
		
		createShader ( _id, sh[0], GL_VERTEX_SHADER, srcVS );
		createShader ( _id, sh[1], GL_FRAGMENT_SHADER, srcFS );
		
		if ( srcGS ) {
			createShader ( _id, sh[2], GL_GEOMETRY_SHADER, srcGS );
		}
		
		glLinkProgram ( _id );
		
		GLint length;
		std::string infoLog;
		glGetProgramiv ( _id, GL_INFO_LOG_LENGTH, &length );
		if ( length ) {
			std::vector<GLchar> buf ( length );
			
			glGetProgramInfoLog ( _id, length, nullptr, &buf[0] );
			
			infoLog = &buf[0];
		}
		
		GLboolean status;
		glGetProgramiv ( _id, GL_LINK_STATUS, &status );
		if ( status != GL_TRUE ) {
			glDeleteProgram ( _id );
			
			deleteShaders ( sh );
			
			throw LinkingException ( infoLog );
		}
		
		detachShaders ( _id, sh );
		
		deleteShaders ( sh );
	}
	
	Shader::~Shader() {
		glDeleteProgram ( _id );
	}
	
}
}
