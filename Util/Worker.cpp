//
//  Worker.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Worker.hpp"

#include "../Game.hpp"

#include "StopWatch.hpp"

namespace JSLib { namespace Util {
	void Worker::RunBackgroundThread (Worker *worker) {
		auto threadId = std::this_thread::get_id();
		
		StopWatch stopWatch;
		
		Game::log << "-- Started background thread #" << threadId << "." << std::endl;
		
		worker->_threadCount++;
		
		while (true) {
			try {
				boost::system::error_code ec;

				worker->_bgThread.run(ec);

				if (ec) {
					Game::log << "-- Error on background thread #" << threadId << ": '" << ec << "'." << std::endl;
				}
				
				break;
			} catch (const std::exception &e ) {
				Game::log << "-- Exception on background thread #" << threadId << ": '" << e.what() << "'." << std::endl;
			} catch (...) {
				Game::log << "-- Exception on background thread #" << threadId << "." << std::endl;
			}
			
			worker->_bgThread.reset();
			
			Game::log << "-- Retarted background thread #" << threadId << "." << std::endl;
		}
		
		Game::log << "-- Finished background thread #" << threadId << ". (+" << stopWatch() << ")" << std::endl;
	}
	
	Worker::Worker() :
	_mainThreadWork(new Work (_mainThread)),
	_bgThreadWork(new Work (_bgThread)),
	_threadCount(0) {
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
			_threads.push_back(std::unique_ptr<std::thread>(new std::thread(RunBackgroundThread, this)));
		}
		
		while ( _threadCount.load() != count ) {
			std::this_thread::yield();
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
