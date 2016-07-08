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

#include "Render/Render.hpp"
#include "Audio/Audio.hpp"

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
			const char *title;
			const char *company;
			
			Window::Settings window;
		};
		
		struct SDLEventsInitFailedException : std::runtime_error {
			SDLEventsInitFailedException() : std::runtime_error("SDL system 'events' failed to initialise."){}
		};

	protected:
		static std::unique_ptr<Game> _game;
		
		Util::StopWatch _stopWatch;
		
		bool _running;
		
		Window::Unique _window;
		
		RenderSystem *_renderSystem = nullptr;
		
		AudioSystem *_audioSystem = nullptr;

		Game(Settings &settings);
		
		void loop();
		
		void poll();
		
	public:
		static Util::Logger log;
		static Util::Worker worker;
		
		static int Run(Settings &settings, RunSettings *runSettings = nullptr) noexcept;
		
		~Game();
	};
}

#endif // #ifndef __JSLIB_GAME_HPP
