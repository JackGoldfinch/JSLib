//
//  Window.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSLIB_WINDOW_CPP

#include "Window.hpp"

#include "Game.hpp"

#pragma warning(once: 4251)
#include <glbinding/Binding.h>
#pragma warning(default: 4251)

namespace JSLib {
	Uint32 Window::fullscreenMode = SDL_WINDOW_FULLSCREEN;
	
	struct DisplayMode {
		friend struct Display;
		
		const unsigned int index, width, height, refreshRate;
		
	private:
		DisplayMode (unsigned int index, const SDL_DisplayMode &displayMode):
		index(index),
		width(displayMode.w),
		height(displayMode.h),
		refreshRate(displayMode.refresh_rate) {}
		
		std::string toString() const {
			std::stringstream ret;
			
			ret  << width << "x" << height << "@" << refreshRate;
			
			return ret.str();
		}
	};
	
	struct Display {
		friend struct DisplayInfo;
		
		const unsigned int index;
		std::string name;
		
		std::vector<DisplayMode> displayModes;
		
	private:
		Display ( unsigned int index):
		index(index) {
			name = SDL_GetDisplayName(index);
			
			int numDisplayModes = SDL_GetNumDisplayModes(index);
			
			for (int i = 0; i < numDisplayModes; ++i) {
				SDL_DisplayMode displayMode;
				if (SDL_GetDisplayMode(index, i, &displayMode) != -1) {
					displayModes.push_back(DisplayMode(i, displayMode));
				}
			}
		}
		
		std::string toString() const {
			std::stringstream ret;
			
			ret << "Display '" << name << "'";
			
			int i = 1;
			for (auto &displayMode : displayModes) {
				ret << "\n\t\t- (" << i++ << ") " << displayMode.toString();
			}
			
			return ret.str();
		}
	};
	
	struct DisplayInfo {
		friend Window;
		
		std::vector<Display> displays;
		
	private:
		DisplayInfo() {
			int numDisplays = SDL_GetNumVideoDisplays();
			
			for (int i = 0; i < numDisplays; ++i) {
				displays.push_back(Display(i));
			}
		}
		
	public:
		void print() const {
			Game::log << "-- Displays:";
			
			int i = 1;
			for (auto &display : displays) {
				Game::log << "\n\t+ (" << i++ << ") " << display.toString();
			}
			
			Game::log << std::endl;
		}
	};
	
	DisplayInfo *displayInfo = nullptr;
	
	Window::Unique Window::Create(const std::string &title, Settings &settings, unsigned int x, unsigned int y) {
		return Unique(new Window(title, settings, x, y));
	}
	
	Window::Window(const std::string &title, Settings &settings, unsigned int x, unsigned int y):
	Util::System ( "Window" ),
	_settings(settings) {
		_fullscreen = _settings.fullscreen;
		
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
			throw SDLVideoInitFailedException();
		}
		
		if (!displayInfo) {
			displayInfo = new DisplayInfo;
		}
		
		displayInfo->print();
		
		_window = SDL_CreateWindow(title.c_str(), x, y, _settings.width, _settings.height, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
		
		if (!_window) {
			throw WindowCreationFailedException();
		}
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		
		SDL_GL_SetSwapInterval(1);
		
		_context = SDL_GL_CreateContext(_window);
		if(!_context) {
			throw OpenGLContextCreationFailedException();
		}
		
		glbinding::Binding::initialize();
		
		{
			Game::log << "-- OpenGL context created:\n";
			Game::log << "\t" << glGetString(GL_VENDOR) << "(" << glGetString(GL_RENDERER) << ", " << glGetString(GL_VERSION) << ")\n";
			
			GLint major, minor;
			glGetIntegerv(GL_MAJOR_VERSION, &major);
			glGetIntegerv(GL_MINOR_VERSION, &minor);
			Game::log << "\tContext version: " << major << "." << minor << "\n";
			
			Game::log << "\tShading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
			
			GLint numExtensions;
			glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
			Game::log << "\t+ Extensions:";
			if ( numExtensions ) {
				for (int i = 0; i < numExtensions; ++i) {
					Game::log << "\n\t\t- (" << i + 1 << ") " << glGetStringi(GL_EXTENSIONS, i);
				}
			} else {
				Game::log << "\n\t\tNone.";
			}
			
			Game::log << std::endl;
		}
		
		glViewport(0, 0, _settings.width, _settings.height);
		//clearColor({.5f, .5f, .5f, 1.f});
		
		started();
	}
	
	Window::~Window() {
		stopping();
		
		SDL_HideWindow(_window);
		
		SDL_GL_DeleteContext(_context);
		
		SDL_DestroyWindow(_window);
		
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}
	
	void Window::clear ( ClearBufferMask cbm ) {
		if ( _clearColor.hasAnimation() || _clearColor.hasChanged() ) {
			glClearColor(_clearColor->r, _clearColor->g, _clearColor->b, _clearColor->a);
		}
		
		glClear ( cbm );
	}
	
	void Window::swap() {
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
	
	void Window::clearColor ( const glm::color4 &clearColor ) {
		_clearColor = clearColor;
	}

	void Window::clearColor ( const glm::color4 &clearColor, const Duration &duration ) {
		_clearColor.animate ( clearColor, duration );
	}
}
