//
//  Game.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSLIB_GAME_CPP

#include <cmath>

#ifndef _WINDOWS

#include <unistd.h>

#endif

#include "Game.hpp"

#include <SDL2/SDL.h>

namespace JSLib {
	std::unique_ptr<Game> Game::_game;
	
	Util::Worker &Game::worker = Util::Worker::Get();
	Util::Logger Game::log;

	fs::path basePath;
	fs::path cwdPath;
	fs::path prefPath;
	
	int Game::Run(const std::string &title, RunSettings *runSettings) noexcept {
		if (_game) {
			throw false;
		}
		
		try {
			_game.reset(new Game(title));
			
			worker.postOnMainThread(std::bind(&Game::loop, _game.get()));
			
			worker.runMainThread();
		} catch (...) {
			log << "Something went terribly wrong..." << std::endl;
		}
		
		return 0;
	}
	
	Game::Game(const std::string &title) {
		std::atexit([](){
			log << "Fin." << std::endl;
		});

		auto cBasePath = SDL_GetBasePath();
		basePath = cBasePath;
		SDL_free(cBasePath);
		
		basePath = basePath.parent_path().parent_path().parent_path();

#ifdef _WINDOWS

		{
			wchar_t cwdBuf[MAX_PATH];
			auto cwd = _wgetcwd(cwdBuf, MAX_PATH);

			cwdPath = cwd;
		}

#else

		char cwdBuf[1024];
		auto cwd = getcwd(cwdBuf, 1024);

		cwdPath = cwd;

#endif

		auto cPrefPath = SDL_GetPrefPath(title.c_str(), "JaySoft");
		prefPath = cPrefPath;
		SDL_free(cPrefPath);

		log.setFile(basePath / (title + ".log").c_str());

		log << "Base path: " << basePath << std::endl;
		log << "CWD path: " << cwdPath << std::endl;
		log << "Pref path: " << prefPath << std::endl;

		if (SDL_InitSubSystem(SDL_INIT_EVENTS|SDL_INIT_VIDEO) < 0) {
			throw false;
		}
		
		std::atexit(SDL_Quit);

		displayModes();

		_window = Window::Create(title, 1280, 720, false);

		_audioSystem = new AudioSystem;
	}
	
	Game::~Game() {
		delete _audioSystem;

		_window.reset();

		SDL_QuitSubSystem(SDL_INIT_EVENTS|SDL_INIT_VIDEO);
	}
	
	void Game::loop() {
		if (worker.hasWork()) {
			poll();
			
			render();
			
			worker.postOnMainThread(std::bind(&Game::loop, this));
		}
	}
	
	void Game::displayModes() {
		log << "--- Displays ---\n";
		
		int numDisplays = SDL_GetNumVideoDisplays();
		int logNumDisplays = std::log10(numDisplays) + 1;
		
		for (int i = 0; i < numDisplays; ++i) {
			auto displayName = SDL_GetDisplayName(i);
			
			log << "- Display (" << log.formattedNumber(i + 1, logNumDisplays) << "/" << log.formattedNumber(numDisplays, logNumDisplays) << "): " << displayName << "\n";
			log << "\t+ Display modes:";
			
			int numDisplayModes = SDL_GetNumDisplayModes(i);
			int logNumDisplayModes = std::log10(numDisplayModes) + 1;
			
			for (int i2 = 0; i2 < numDisplayModes; ++i2) {
				SDL_DisplayMode displayMode;
				if (SDL_GetDisplayMode(i, i2, &displayMode) != -1) {
					log << "\n\t\t(" << log.formattedNumber(i2 + 1, logNumDisplayModes) << "/" << log.formattedNumber(numDisplayModes, logNumDisplayModes) << ") " << displayMode.w << "x" << displayMode.h << "@" << displayMode.refresh_rate << "(" << SDL_GetPixelFormatName(displayMode.format) << ")";
				}
			}
			
			log << std::endl;
		}
	}
	
	void Game::poll() {
		SDL_Event event;
		
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					worker.reset();
					return;
			}
		}
	}
	
	void Game::render() {
		_window->swap();
	}
}
