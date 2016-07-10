//
//  Render.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 06.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#define __JSL_RENDER_RENDER_CPP

#include "Render.hpp"

#include "Quad.hpp"
#include "Shader.hpp"

#include "../Game.hpp"

namespace JSLib {
namespace Render {
	
	Quad *quad;
	
	System::System ( Window *window ):
	Util::System ( "Render" ),
	_window ( window ) {
		Shader::Fill();
		
		quad = new Quad;
		
		auto shp = Shader::Get ( "simple" );
		shp->bind();
		
		started();
	}
	
	System::~System() {
		stopping();
		
		delete quad;
		
		Shader::Clear();
	}
	
	void System::process() {
		_window->clear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		IRenderable::Render();
		
		quad->render();
		
		_window->swap();
	}
	
} // namespace Render
} // namespace JSLib
