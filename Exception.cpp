//
//  Exception.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 09.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "Exception.hpp"

namespace JSLib {
	
	Exception::Exception ( const std::string &brief, const std::string &detail ):
	_brief ( brief ),
	_detail ( detail ) {
		
	}
	
}
