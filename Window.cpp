//
//  Window.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSLIB_WINDOW

#include "Window.hpp"

#include <string>

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
		
		_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_HIDDEN);
		
		if (!_window) {
			throw false;
		}
		
		SDL_ShowWindow(_window);
	}
	
	Window::~Window() {
		SDL_HideWindow(_window);
		
		SDL_DestroyWindow(_window);
		
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}
	
	void Window::swap() {
		
	}
	
	void Window::toggleFullscreen() {
		
	}
}
