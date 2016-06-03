//
//  Window.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSLIB_WINDOW_CPP

#include "Window.hpp"

namespace JSLib {
	Uint32 Window::fullscreenMode = SDL_WINDOW_FULLSCREEN;
	
	Window::Unique Window::Create(const std::string &title, unsigned int width, unsigned int height, bool fullscreen, unsigned int x, unsigned int y) {
		return Unique(new Window(title, width, height, fullscreen, x, y));
	}
	
	Window::Window(const std::string &title, unsigned int width, unsigned int height, bool fullscreen, unsigned int x, unsigned int y):
	_fullscreen(fullscreen) {
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
			throw false;
		}
		
		_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
		
		if (!_window) {
			throw false;
		}
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		
		SDL_GL_SetSwapInterval(1);
		
		_context = SDL_GL_CreateContext(_window);
		if(!_context) {
			throw false;
		}
		
		glbinding::Binding::initialize();
		
		glViewport(0, 0, width, height);
		glClearColor(.5f, .5f, .5f, 1.f);
		
		SDL_ShowWindow(_window);
	}
	
	Window::~Window() {
		SDL_HideWindow(_window);
		
		SDL_GL_DeleteContext(_context);
		
		SDL_DestroyWindow(_window);
		
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}
	
	void Window::swap() {
		glClear(GL_COLOR_BUFFER_BIT);
		
		SDL_GL_SwapWindow(_window);
	}
	
	void Window::toggleFullscreen() {
		if (_fullscreen) {
			SDL_SetWindowFullscreen(_window, 0);
			_fullscreen = false;
		} else {
			SDL_SetWindowFullscreen(_window, fullscreenMode);
			_fullscreen = true;
		}
	}
}
