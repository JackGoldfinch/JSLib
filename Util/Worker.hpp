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

#include <boost/asio.hpp>
using boost::asio::io_service;

namespace JSLib { namespace Util {
	class JSLIB_EXPORT Worker {
	public:
		typedef io_service::work Work;
		typedef std::unique_ptr<Work> UniqueWork;
		
	protected:
		io_service _mainThread;
		UniqueWork _mainThreadWork;
		
		io_service _bgThread;
		UniqueWork _bgThreadWork;
		
		Worker();
		
	public:
		~Worker();
		
		static Worker &Get();
		
		std::size_t runMainThread();
		
		template <class T>
		void postOnMainThread(T &&handler) {
			_mainThread.post(handler);
		}
		
		template <class T>
		void postOnBackgroundThread(T &&handler) {
			_bgThread.post(handler);
		}
		
		void reset();
		
		bool hasWork() const {
			return (_mainThreadWork || _bgThreadWork);
		}
	};
}}

#endif // #ifndef __JSLIB_UTIL_WORKER_HPP
