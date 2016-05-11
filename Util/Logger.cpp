//
//  Logger.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Logger.hpp"

namespace JSLib { namespace Util {
	Logger::~Logger() {
		closeFile();
	}
	
	void Logger::setFile(const std::string &file) {
		closeFile();
		
		_file = new std::fstream(file, std::ios::out);
		if ((! _file) || (! _file->is_open())) {
			_file = nullptr;
			throw false;
		}
	}
	
	void Logger::closeFile() {
		if (_file) {
			_file->close();
			
			delete _file;
			_file = nullptr;
		}
	}
}}
