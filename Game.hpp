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

#include <boost/asio.hpp>
using boost::asio::io_service;

#include <glm/glm.hpp>

#ifdef __JSLIB_GAME

#else

#endif // #ifdef __JSLIB_GAME

#include "Window.hpp"

namespace JSLib {
	class JSLIB_EXPORT Game {
	public:
		typedef io_service::work Work;
		typedef std::unique_ptr<Work> UniqueWork;
		
	protected:
		static std::unique_ptr<Game> _game;
		
		static io_service _mainThread;
		static UniqueWork _mainThreadWork;

		static io_service _bgThread;
		
		Window::Unique _window;
		
		Game(const std::string &title);
		
		void loop();
		
		void displayModes();
		
		void poll();
		void render();
		
	public:
		static int Run(const std::string &title, int argc, char *args[]);
		
		~Game();
	};
}

#endif // #ifndef __JSLIB_GAME_HPP
