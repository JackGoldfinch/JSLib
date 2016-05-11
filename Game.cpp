//
//  Game.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSLIB_GAME

#include <cmath>

#include "Game.hpp"

#include <SDL2/SDL.h>

namespace JSLib {
	std::unique_ptr<Game> Game::_game;
	
	Util::Worker &Game::worker = Util::Worker::Get();
	Util::Logger Game::log;
	
	int Game::Run(const std::string &title, int argc, char *args[]) {
		if (_game) {
			throw false;
		}
		
		try {
			log.setFile(title + ".log");
			
			_game.reset(new Game(title));
			
			worker.postOnMainThread(std::bind(&Game::loop, _game.get()));
			
			worker.runMainThread();
		} catch (...) {
			log << "Something went terribly wrong..." << std::endl;
		}
		
		return 0;
	}
	
	Game::Game(const std::string &title) {
		if (SDL_InitSubSystem(SDL_INIT_EVENTS|SDL_INIT_VIDEO) < 0) {
			throw false;
		}
		
		std::atexit(SDL_Quit);
		
		displayModes();
		
		_window = Window::Create(title, 1280, 720, false);
	}
	
	Game::~Game() {
		_window.reset();
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
			
			log << "- Display (" << log.formattedNumber(i + 1, logNumDisplays) << "/" << log.formattedNumber(numDisplays, logNumDisplays) << "): " << displayName << std::endl;
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
