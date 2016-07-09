//
//  Render.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSL_RENDER_RENDER_CPP

#include "Render.hpp"

#include "Shader.hpp"

#include "../Game.hpp"

namespace JSLib {
namespace Render {
	
	System::System ( Window *window ):
	Util::System ( "Render" ),
	_window ( window ) {
		auto vsh = "#version 330\n"
			"void main() {\n"
			"\tgl_Position = vec4(0.0, 0.0, 0.0, 0.0);\n"
			"}\n"
			"";
		
		auto fsh = "#version 330\n"
			"out vec4 finalColor;\n"
			"void main() {\n"
			"finalColor = vec4(1.0,1.0,1.0,1.0);\n"
			"}\n"
			"";
		
		try {
			auto shader = new Shader ( vsh, nullptr );
			
			delete shader;
		} catch ( const OpenGLException &e ) {
			Game::log << e.what() << std::endl;
		}
		
		started();
	}
	
	System::~System() {
		stopping();
	}
	
	void System::process() {
		IRenderable::Render();
		
		_window->swap();
	}
	
} // namespace Render
} // namespace JSLib
