//
//  Game.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_GAME_HPP
#define __JSLIB_GAME_HPP

#include "JSLib_Export.hpp"

#include <string>
#include <iostream>
#include <memory>

#include <glm/glm.hpp>

#ifdef __JSLIB_GAME

#else

#endif // #ifdef __JSLIB_GAME

#include "Util/Worker.hpp"

#include "Window.hpp"

namespace JSLib {
	class JSLIB_EXPORT Game {
	protected:
		static std::unique_ptr<Game> _game;
		
		Window::Unique _window;
		
		Game(const std::string &title);
		
		void loop();
		
		void displayModes();
		
		void poll();
		void render();
		
	public:
		static Util::Worker &worker;
		
		static int Run(const std::string &title, int argc, char *args[]);
		
		~Game();
	};
}

#endif // #ifndef __JSLIB_GAME_HPP
