//
//  IRenderable.cpp
//  JSLib
//
//  Created by Johannes Stieglitz on 08.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#include "IRenderable.hpp"

#include "../Game.hpp"

namespace JSLib {
namespace Render {
	
	IRenderable::Set IRenderable::_renderables;
	
	void IRenderable::Render() {
		Set visible;
		
		for ( auto renderable : _renderables ) {
			if ( false ) {
				visible.insert ( renderable );
			}
		}
		
		for ( auto renderable : visible ) {
			renderable->render();
		}
	}
	
	IRenderable::IRenderable() {
		Game::log << "IRenderable constructed." << std::endl;
	}
	
	IRenderable::~IRenderable() {
		Game::log << "IRenderable destructed." << std::endl;
	}
	
	void *IRenderable::operator new ( std::size_t n ) {
		auto p = ::operator new ( n );
		
		_renderables.insert (  ( IRenderable* ) p );
		
		return p;
	}
	
	void IRenderable::operator delete ( void *p, std::size_t n ) {
		_renderables.erase ( ( IRenderable* ) p );
		
		::operator delete ( p );
	}
	
}
}
