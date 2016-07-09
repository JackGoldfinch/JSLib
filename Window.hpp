//
//  Window.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_WINDOW_HPP
#define __JSLIB_WINDOW_HPP

#include "JSLib_Export.hpp"

#include <string>
#include <memory>

#ifdef __JSLIB_WINDOW_CPP

#include "JSLib_OpenGL.hpp"

#pragma warning(once: 4251)
#include <glbinding/Binding.h>
#pragma warning(default: 4251)
using namespace gl;

#include <SDL2/SDL.h>

#define JSLIB_GLM_NO_FWD

#else

#include <SDL2/SDL_video.h>

#endif // #ifdef __JSLIB_WINDOW_CPP

#include "JSLib_GLM.hpp"

#include "Util/Animation.hpp"

#include "Util/System.hpp"

#include "Exception.hpp"

namespace JSLib {
	
	/**
		@brief This is the sole window that is created by the game.
	 */
	
	class JSLIB_EXPORT Window : Util::System {
	public:
		struct SDLVideoInitFailedException : public Exception {
			SDLVideoInitFailedException() : Exception("SDL Video Initialisation failed") {}
		};
		
		struct WindowCreationFailedException : public Exception {
			WindowCreationFailedException() : Exception("Window creation failed") {}
		};
		
		struct OpenGLContextCreationFailedException : public Exception {
			OpenGLContextCreationFailedException() : Exception("Creation of OpenGL context failed") {}
		};
		
		struct Settings {
			unsigned int width, height;
			bool fullscreen;
		};
		
		typedef std::unique_ptr<Window> Unique;
		
		static Uint32 fullscreenMode;
		
		static Unique Create(const std::string &title, Settings &settings, unsigned int x = SDL_WINDOWPOS_UNDEFINED, unsigned int y = SDL_WINDOWPOS_UNDEFINED);
		
	protected:
		Settings &_settings;
		
		SDL_Window *_window;
		SDL_GLContext _context;
		
		bool _fullscreen;
		
		Avec4 _clearColor;

		Window(const std::string &title, Settings &settings, unsigned int x = SDL_WINDOWPOS_UNDEFINED, unsigned int y = SDL_WINDOWPOS_UNDEFINED);
		
	public:
		~Window();
		
		void swap();
		
		void show() const {
			SDL_ShowWindow(_window);
		}
		
		void toggleFullscreen();
		
		void setTitle ( const std::string &title ) {
			SDL_SetWindowTitle ( _window, title.c_str() );
		}

		void clearColor ( const glm::color4 &clearColor );
		void clearColor ( const glm::color4 &clearColor, const Duration &duration );
	};
}

#endif // #ifndef __JSLIB_WINDOW_HPP
