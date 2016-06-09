//
//  Logger.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Logger.hpp"

namespace JSLib {
namespace Util {
	
	const char *Logger::divider = ": ";
	
	Logger::Logger() {
		_intermediateStringStream.imbue(std::locale(std::locale(""), new pt::time_facet("%Y/%m/%d %H:%M:%S.%f")));
	}

	Logger::~Logger() {
		closeFile();
	}
	
	void Logger::setFile(const fs::path &file) {
		closeFile();
		
		_file = new std::fstream(file.c_str(), std::ios::out);
		if ((! _file) || (! _file->is_open())) {
			if (_file) {
				delete _file;
			}
			
			_file = nullptr;
			
			*this << "Could not create logfile at " << file << "." << std::endl;
		}
	}
	
	void Logger::closeFile() {
		if (_file) {
			_file->close();
			
			delete _file;
			_file = nullptr;
		}
	}
	
}
}
