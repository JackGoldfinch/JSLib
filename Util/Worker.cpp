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

		Game::log << "Started background thread #" << threadId << std::endl;

		while (true) {
			try {
				boost::system::error_code ec;

				service->run(ec);

				if (ec) {
					Game::log << "Error in background thread #" << threadId << ": " << ec << std::endl;
				}
				break;
			} catch (const std::exception &e ) {
				Game::log << "Exception in background thread #" << threadId << ": " << e.what() << std::endl;
			}
		}

		Game::log << "Finished background thread #" << threadId << std::endl;
	}

	Worker &Worker::Get() {
		static Worker me;
		
		return me;
	}
	
	Worker::Worker() :
	_mainThreadWork(new Work (_mainThread)),
	_bgThreadWork(new Work (_bgThread)) {
		for (unsigned int i = 0; i < 3; ++i) {
			_threads.push_back(std::unique_ptr<std::thread>( new std::thread(RunBackgroundThread, &_bgThread)));
		}
	}
	
	Worker::~Worker() {
		reset();
	}
	
	std::size_t Worker::runMainThread() {
		return _mainThread.run();
	}
	
	void Worker::reset() {
		_bgThread.stop();
		_bgThreadWork.reset();

		for (auto &thread : _threads) {
			thread->join();
		}
		_threads.clear();

		_mainThread.stop();
		_mainThreadWork.reset();
	}
}}
