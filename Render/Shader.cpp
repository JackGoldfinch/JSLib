//
//  Shader.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 08.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Shader.hpp"

#include "../Util/StopWatch.hpp"

#include "../Game.hpp"

#include <vector>
#include <fstream>

namespace JSLib {
namespace Render {
	
#pragma mark predefined shaders
	
	struct shader_t {
		const char *vsh = nullptr;
		const char *fsh = nullptr;
		const char *gsh = nullptr;
		
		shader_t ( const char *v, const char *f, const char *g = nullptr ):
		vsh ( v ),
		fsh ( f ),
		gsh ( g ) {}
	};
	
	shader_t simple {
		GLSL(
			 layout (location = 0 ) in vec3 position;
			 
			 void main() {
				 gl_Position = vec4 ( position, 1.0 );
			 }
		),
		
		GLSL(
			layout ( location = 0 ) out vec4 finalColor;
			 
			 void main() {
				 finalColor = vec4 ( 1.0, 1.0, 1.0, 1.0 );
			 }
		)
	};
	
#pragma mark Globally private stuff
	
	const int numShaders = 3;
	
	template <void(*_getiv)(GLuint, GLenum, GLint*), void(*_getInfoLog)(GLuint, GLsizei, GLsizei*, GLchar*)>
	void getInfoLog ( GLuint &sh, std::string &target ) {
		GLint length;
		_getiv ( sh, GL_INFO_LOG_LENGTH, &length );
		if ( length ) {
			std::vector<GLchar> buf ( length );
			
			_getInfoLog ( sh, length, nullptr, &buf[0] );
			
			target = &buf[0];
		}
	}
	
	void createShader ( GLuint &p, GLuint &sh, GLenum type, const char *source ) {
		sh = glCreateShader ( type );
		
		if ( !sh ) {
			throw OpenGLException();
		}
		
		glShaderSource ( sh, 1, &source, nullptr );
		
		glCompileShader ( sh );
		
		std::string infoLog;
		getInfoLog<glGetShaderiv, glGetShaderInfoLog>(sh, infoLog);
		
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
			if ( sh[i] ) {
				glDetachShader ( p, sh[i] );
			}
		}
	}
	
	void deleteShaders ( GLuint *sh ) {
		for ( GLuint i = 0; i < numShaders; ++i ) {
			glDeleteShader ( sh[i] );
		}
	}
	
#pragma mark Shader
	
	const fs::path Shader::_path { "Shaders" };
	
	Shader::Map Shader::_shaders;
	
	Shader::KeySet Shader::_wip, Shader::_blacklist;
	
	std::mutex Shader::_shadersMutex, Shader::_wipMutex, Shader::_blacklistMutex;
	
	Shader *Shader::_active = nullptr;
	
	void Shader::Fill() {
		Post ( "simple", simple.vsh, simple.fsh );
	}
	
	void Shader::Clear() {
		MutexGuard guard ( _shadersMutex );
		_shaders.clear();
	}
	
	void Shader::Post ( const char *key, Shader *shader ) {
		if ( ! shader ) {
			return;
		}
		
		MutexGuard guard ( _shadersMutex );
		_shaders.insert ( Shader::Map::value_type ( key, Unique ( shader ) ) );
		
	}
	
	void Shader::Post ( const char *key, const char *vsh, const char *fsh, const char *gsh ) {
		try {
			auto shader = new Shader ( key, vsh, fsh, gsh );
			Post ( key, shader );
		} catch ( const Exception &e ) {
			
		}
	}
	
	Shader *Shader::Get ( const char *key ) {
		Shader *shader = nullptr;
		
		try {
			MutexGuard guard ( _shadersMutex );
			shader = _shaders.at ( key ).get();
		} catch ( const std::out_of_range &e ) {
			auto path = _path / key;
			
			if ( fs::exists ( path ) ) {
				_wip.insert ( key );
				
				Game::worker.postOnBackgroundThread ( [key, &path]() {
					std::ifstream file ( path.c_str(), std::ios::in );
					
					
				} );
			} else {
				_blacklist.insert ( key );
			}
		}
		
		return shader;
	}
	
	void Shader::Bind ( Shader *shader ) {
		if ( _active != shader ) {
			_active = shader;
			
			glUseProgram ( _active->_id );
		}
	}
	
	Shader::Shader ( const fs::path &name, const char *srcVS, const char *srcFS, const char *srcGS ):
		_name ( name ) {
		Util::StopWatch stopwatch;
		
		Game::log << "Creating shader program " << _name << "..." << std::endl;
			
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
			
		std::string infoLog;
		getInfoLog<glGetProgramiv, glGetProgramInfoLog>(_id, infoLog);
		
		GLboolean status;
		glGetProgramiv ( _id, GL_LINK_STATUS, &status );
		if ( status != GL_TRUE ) {
			glDeleteProgram ( _id );
			
			deleteShaders ( sh );
			
			throw LinkingException ( infoLog );
		}
		
			//detachShaders ( _id, sh );
		
			//deleteShaders ( sh );
			
		glValidateProgram ( _id );
		
		std::string validationLog;
		getInfoLog<glGetProgramiv, glGetProgramInfoLog>(_id, validationLog);
		
		glGetProgramiv(_id, GL_VALIDATE_STATUS, &status);
		if ( status != GL_TRUE ) {
			Game::log << _name << " -- " << validationLog << std::endl;
		}
			
		Game::log << "Creating shader program " << _name << "... OK. (+" << stopwatch() << ")" << std::endl;
	}
	
	Shader::~Shader() {
		glDeleteProgram ( _id );
	}
	
}
}
