//
//  Shader.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 08.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_SHADER_HPP
#define __JSLIB_RENDER_SHADER_HPP

/****************************
 * Makro by https://open.gl *
 ****************************/
#define GLSL(src) "#version 330 core\n" #src

#include "../JSLib_Export.hpp"

#include "../JSLib_OpenGL.hpp"

#include <memory>
#include <mutex>
#include <map>
#include <set>

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

typedef std::lock_guard<std::mutex> MutexGuard;

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
		
		typedef std::unique_ptr<Shader> Unique;
		typedef std::map<const char*, Unique> Map;
		typedef std::set<const char*> KeySet;
		
	protected:
		static Map _shaders;
		
		static KeySet _wip, _blacklist;
		
		static std::mutex _shadersMutex, _wipMutex, _blacklistMutex;
		
		static Shader *_active;
		
		GLuint _id;
		
		const fs::path &_name;
		
		Shader ( const fs::path &name, const char *srcVS, const char *srcFS, const char *srcGS = nullptr );
		
	public:
		static const fs::path _path;
		
		static void Fill();
		static void Clear();
		
		static void Post ( const char *key, Shader *shader );
		static void Post ( const char *key, const char *vsh, const char *fsh, const char *gsh = nullptr );
		static Shader *Get ( const char *key );
		
		static Shader *Active() {
			return _active;
		}
		static void Bind ( Shader *shader );
		
		virtual ~Shader();
		
		void bind() {
			Bind ( this );
		}
	};
	
}
}

#endif // #ifndef __JSLIB_RENDER_SHADER_HPP
