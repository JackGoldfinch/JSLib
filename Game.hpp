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

#ifdef __JSLIB_GAME_CPP

#else

#endif // #ifdef __JSLIB_GAME_CPP

#include "Util/Worker.hpp"
#include "Util/Logger.hpp"

#include "Audio/System.hpp"

#include "Window.hpp"

namespace JSLib {
	class JSLIB_EXPORT Game {
	public:
		struct RunSettings {
			int argc;
			char **args;

			RunSettings() {
				memset(this, 0, sizeof(RunSettings));
			}
		};

		struct Settings {

		};

	protected:
		static std::unique_ptr<Game> _game;
		
		Window::Unique _window;
		
		AudioSystem *_audioSystem = nullptr;

		Game(const std::string &title);
		
		void loop();
		
		void displayModes();
		
		void poll();
		void render();
		
	public:
		static Util::Worker &worker;
		static Util::Logger log;
		
		static int Run(const std::string &title, RunSettings *runSettings = nullptr) noexcept;
		
		~Game();
	};
}

#endif // #ifndef __JSLIB_GAME_HPP
