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

#ifdef __JSLIB_WINDOW

#include "JSLib_OpenGL.hpp"

#pragma warning(once: 4251)
#include <glbinding/Binding.h>
#pragma warning(default: 4251)
using namespace gl;

#include <SDL2/SDL.h>

#else

#include <SDL2/SDL_video.h>

#endif // #ifdef __JSLIB_WINDOW

namespace JSLib {
	class JSLIB_EXPORT Window {
	public:
		typedef std::unique_ptr<Window> Unique;
		
		static Uint32 fullscreenMode;
		
		static Unique Create(const std::string &title, unsigned int width, unsigned int height, bool fullscreen, unsigned int x = SDL_WINDOWPOS_UNDEFINED, unsigned int y = SDL_WINDOWPOS_UNDEFINED);
		
	protected:
		SDL_Window *_window;
		SDL_GLContext _context;
		
		bool _fullscreen;
		
		Window(const std::string &title, unsigned int width, unsigned int height, bool fullscreen, unsigned int x = SDL_WINDOWPOS_UNDEFINED, unsigned int y = SDL_WINDOWPOS_UNDEFINED);
		
	public:
		~Window();
		
		void swap();
		
		void toggleFullscreen();
	};
}

#endif // #ifndef __JSLIB_WINDOW_HPP