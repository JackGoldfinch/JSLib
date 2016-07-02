//
//  Game.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSLIB_GAME_CPP

#ifndef _WINDOWS

#include <unistd.h>

#endif

#include "Game.hpp"

#include "Util/Animation.hpp"

#include <SDL2/SDL.h>

namespace JSLib {
	
	std::unique_ptr<Game> Game::_game;
	
	Util::Logger Game::log;
	Util::Worker Game::worker;

	fs::path basePath;
	fs::path cwdPath;
	fs::path prefPath;
	
	int Game::Run(Settings &settings, RunSettings *runSettings) noexcept {
		if (_game) {
			return -1;
		}
		
		log << "Platform: " << SDL_GetPlatform() << std::endl;

		auto cBasePath = SDL_GetBasePath();
		basePath = cBasePath;
		SDL_free(cBasePath);
		
#ifdef _WINDOWS
		
		basePath = basePath.parent_path().parent_path().parent_path();
		
		{
			wchar_t cwdBuf[MAX_PATH];
			auto cwd = _wgetcwd(cwdBuf, MAX_PATH);
			
			cwdPath = cwd;
		}
		
#elif defined __APPLE__
		
		basePath = basePath / "Content" / "Resources";
		
#else
		
		basePath = basePath.parent_path().parent_path().parent_path();
		
		char cwdBuf[1024];
		auto cwd = getcwd(cwdBuf, 1024);
		
		cwdPath = cwd;
		
#endif
		
		auto cPrefPath = SDL_GetPrefPath(settings.company, settings.title);
		prefPath = cPrefPath;
		SDL_free(cPrefPath);
		
		auto logPath = prefPath / settings.title;
		logPath += ".log";
		log.setFile(logPath);
		
		log << "-- Base path: " << basePath << std::endl;
		log << "-- CWD path: " << cwdPath << std::endl;
		log << "-- Pref path: " << prefPath << std::endl;
		
		try {
			_game.reset(new Game(settings));
			
			_game->loop();
		} catch (const std::exception &e) {
			log << "Something went terribly wrong..." << std::endl;
			log << "This is what we've got: '" << e.what() << "'." << std::endl;
		} catch (...) {
			log << "Something went terribly wrong..." << std::endl;
		}
		
		_game.reset();
			
		log << "Fin." << std::endl;
		
		return 0;
	}
	
	Game::Game(Settings &settings):
	_running(true) {
		log << "Game: Starting..." << std::endl;
		
		if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {
			throw SDLEventsInitFailedException();
		}
		
		std::atexit(SDL_Quit);

		_window = Window::Create(settings.title, settings.window);

		_audioSystem = new AudioSystem;
		
		worker.addThreads();

		log << "Game: Starting... OK. (+" << _stopWatch() << ")" << std::endl;
	}
	
	Game::~Game() {
		log << "Game: Stopping..." << std::endl;
		
		worker.reset();

		delete _audioSystem;

		_window.reset();

		SDL_QuitSubSystem(SDL_INIT_EVENTS);
		
		log << "Game: Stopping... OK. (+" << _stopWatch() << ")" << std::endl;
	}
	
	void Game::loop() {
		render();
		
		_window->show();
		
		while (_running) {
			poll();
			
			Util::IAnimatable::Process();
			
			render();
			
			worker.runMainThreadQueue();
		}
	}
	
	void Game::poll() {
		SDL_Event event;
		
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					_running = false;
					return;
					
				case SDL_MOUSEBUTTONDOWN:
					
					return;
					
				case SDL_MOUSEBUTTONUP:
					_window->clearColor ( {0.f, 0.f, 0.f, 1.f} );
					_window->clearColor ( {1.f, 1.f, 1.f, 1.f}, std::chrono::seconds(3) );
					return;
			}
		}
	}
	
	void Game::render() {
		_window->swap();
	}
		
} // namespace JSLib
