//
//  Exception.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#ifndef __JSLIB_EXCEPTION_HPP
#define __JSLIB_EXCEPTION_HPP

#include "JSLib_Export.hpp"

#include <exception>
#include <string>

namespace JSLib {
	
	class JSLIB_EXPORT Exception : public std::exception {
	protected:
		const std::string &_brief;
		const std::string &_detail;
		
	public:
		Exception ( const std::string &brief, const std::string &detail = "" );
		
		const std::string &brief() const {
			return _brief;
		}
		
		const std::string &detail() const {
			return _detail;
		}
		
		virtual ~Exception() {}
	};
	
}

#endif // #ifndef __JSLIB_EXCEPTION_HPP
