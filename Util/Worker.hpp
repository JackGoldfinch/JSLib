//
//  Worker.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_UTIL_WORKER_HPP
#define __JSLIB_UTIL_WORKER_HPP

#include "../JSLib_Export.hpp"

#include <memory>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
using boost::asio::io_service;

namespace JSLib { namespace Util {
	class JSLIB_EXPORT Worker {
	public:
		typedef io_service Service;
		typedef Service::work Work;
		typedef std::unique_ptr<Work> UniqueWork;
		
	protected:
		static void RunBackgroundThread (Worker *worker);

		Service _mainThread;
		UniqueWork _mainThreadWork;
		
		Service _bgThread;
		UniqueWork _bgThreadWork;
		
		std::vector<std::unique_ptr<std::thread>> _threads;
		
		std::atomic<unsigned int> _threadCount;
		
	public:
		Worker();
		~Worker();
		
		static Worker &Get();
		
		boost::system::error_code runMainThreadQueue();
		
		void addThreads(unsigned int count = std::thread::hardware_concurrency() - 1);
		
		template <typename T>
		void postOnMainThread(T &&handler) {
			_mainThread.post(handler);
		}
		
		template <typename T>
		void postOnBackgroundThread(T &&handler) {
			_bgThread.post(handler);
		}
		
		template <typename T>
		void postOnBackgroundThread ( T &&handler, void (*completionHandler) ( typename std::result_of<T()>::type result ) ) {
			_bgThread.post([this, &handler, completionHandler]() {
				auto result = handler();
				
				_mainThread.post ( std::bind ( completionHandler, result ) );
			});
		}
		
		template <typename T>
		void postOnBackgroundThread ( T &&handler, void (*completionHandler)() ) {
			_bgThread.post([this, &handler, completionHandler]() {
				handler();
				
				_mainThread.post ( completionHandler );
			});
		}
		
		void reset();
		
		bool hasWork() const {
			return (_mainThreadWork || _bgThreadWork);
		}
	};
}}

#endif // #ifndef __JSLIB_UTIL_WORKER_HPP
