//
//  Shader.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 08.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#ifndef __JSLIB_RENDER_SHADER_HPP
#define __JSLIB_RENDER_SHADER_HPP

#include "../JSLib_Export.hpp"

#include "../JSLib_OpenGL.hpp"

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

namespace JSLib {
namespace Render {
	
	class JSLIB_EXPORT Shader {
	public:
		struct IncompleteException : public OpenGLException {
			IncompleteException() : OpenGLException ( "A shader needs at least vertex and fragment shading components." ){}
		};
		
		struct CompilationException : public OpenGLException {
			CompilationException ( const std::string &infoLog ) : OpenGLException ( "Shader Compilation Error:\n" + infoLog ){}
		};
		
		struct LinkingException : public OpenGLException {
			LinkingException ( const std::string &infoLog ) : OpenGLException ( "Shader Linking Error:\n" + infoLog ){}
		};
		
	protected:
		GLuint _id;
		
	public:
		Shader ( const char *srcVS, const char *srcFS, const char *srcGS = nullptr );
		virtual ~Shader();
	};
	
}
}

#endif // #ifndef __JSLIB_RENDER_SHADER_HPP
