//
//  Worker.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Worker.hpp"

#include "Logger.hpp"

#include "../Game.hpp"

namespace JSLib { namespace Util {
	void Worker::RunBackgroundThread (Service *service) {
		auto threadId = std::this_thread::get_id();
		
		Game::log << "-- Started background thread #" << threadId << "." << std::endl;
		
		while (true) {
			try {
				boost::system::error_code ec;

				service->run(ec);

				if (ec) {
					Game::log << "-- Error on background thread #" << threadId << ": '" << ec << "'." << std::endl;
				}
				
				break;
			} catch (const std::exception &e ) {
				Game::log << "-- Exception on background thread #" << threadId << ": '" << e.what() << "'." << std::endl;
			} catch (...) {
				Game::log << "-- Exception on background thread #" << threadId << "." << std::endl;
			}
			
			service->reset();
			
			Game::log << "-- Retarted background thread #" << threadId << "." << std::endl;
		}
		
		Game::log << "-- Finished background thread #" << threadId << "." << std::endl;
	}
	
	Worker::Worker() :
	_mainThreadWork(new Work (_mainThread)),
	_bgThreadWork(new Work (_bgThread)) {
		
	}
	
	Worker::~Worker() {
		reset();
	}
	
	boost::system::error_code Worker::runMainThreadQueue() {
		boost::system::error_code ec;
		
		_mainThread.poll(ec);
		_mainThread.reset();
		
		return ec;
	}
	
	void Worker::addThreads(unsigned int count) {
		for (unsigned int i = 0; i < count; ++i) {
			_threads.push_back(std::unique_ptr<std::thread>(new std::thread(RunBackgroundThread, &_bgThread)));
		}
	}
	
	void Worker::reset() {
		_bgThreadWork.reset();
		while (!_bgThread.stopped()) {}

		for (auto &thread : _threads) {
			thread->join();
		}
		_threads.clear();

		_mainThreadWork.reset();
	}
}}
