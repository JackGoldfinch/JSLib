//
//  Logger.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_UTIL_LOGGER_HPP
#define __JSLIB_UTIL_LOGGER_HPP

#include "../JSLib_Export.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <mutex>
#include <thread>
#include <map>
#include <iomanip>

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include <boost/date_time/posix_time/posix_time.hpp>
namespace pt = boost::posix_time;

#include "Worker.hpp"

namespace JSLib { namespace Util {
	class JSLIB_EXPORT Logger {
	public:
		typedef std::map<std::thread::id, std::stringstream> StringStreamMap;
		typedef std::ostream &(*stream_function)(std::ostream&);
		
	protected:
		std::mutex _mutex;
		
		StringStreamMap _stringStreamMap;
		
		std::stringstream _intermediateStringStream;

		std::fstream *_file = nullptr;

		std::stringstream &getStringStream() {
			return _stringStreamMap[std::this_thread::get_id()];
		}
		
	public:
		Logger();
		~Logger();
		
		void setFile(const fs::path &file);
		void closeFile();
		
		template <class T>
		Logger &operator<<(const T &t) {
			getStringStream() << t;
			
			return *this;
		}
		
		Logger &operator<<(stream_function func) {
			_mutex.lock();

			auto &stringstream = getStringStream();

			if (func == (stream_function)std::endl) {
				_intermediateStringStream << pt::microsec_clock::local_time();

				std::cout << _intermediateStringStream.str() << ": " << stringstream.str() << "\n";
				std::cout.flush();
				
				if (_file) {
					*_file << _intermediateStringStream.str() << ": " << stringstream.str() << "\n";
					_file->flush();
				}
				
				_intermediateStringStream.str("");
				stringstream.str("");
			} else {
				func(stringstream);
			}
			
			_mutex.unlock();

			return *this;
		}
		
		template <class T>
		std::string formattedNumber(const T &i, unsigned int width, char fill = '0') {
			std::stringstream stream;
			stream << std::setw(width) << std::setfill(fill) << i;
			
			return stream.str();
		}
	};
}}

#endif // #ifndef __JSLIB_UTIL_LOGGER_HPP
