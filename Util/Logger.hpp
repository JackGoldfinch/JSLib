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

#include "Worker.hpp"

namespace JSLib { namespace Util {
	class JSLIB_EXPORT Logger {
	public:
		typedef std::map<std::thread::id, std::stringstream> StringStreamMap;
		typedef std::ostream &(*stream_function)(std::ostream&);
		
	protected:
		std::mutex _mutex;
		
		StringStreamMap _stringStreamMap;
		
		std::fstream *_file = nullptr;
		
		std::stringstream &getStringStream() {
			return _stringStreamMap[std::this_thread::get_id()];
		}
		
	public:
		~Logger();
		
		void setFile(const std::string &file);
		void closeFile();
		
		template <class T>
		Logger &operator<<(const T &t) {
			getStringStream() << t;
			
			return *this;
		}
		
		Logger &operator<<(stream_function func) {
			auto &stringstream = getStringStream();
			
			func(stringstream);
			
			if (func == (stream_function)std::endl) {
				std::cout << stringstream.str();
				
				if (_file) {
					*_file << stringstream.str();
				}
				
				stringstream.str("");
			}
			
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
