//
//  VertexArray.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 25.07.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_RENDER_OPENGL_VERTEXARRAY_HPP
#define __JSLIB_RENDER_OPENGL_VERTEXARRAY_HPP

namespace JSLib {
namespace Render {
namespace OpenGL {
	
	class JSLIB_EXPORT VertexArray : public Object, public IBindable {
	protected:
		static VertexArray *_boundVertexArray;
		
	public:
		static VertexArray *Bound();
		static bool IsBound ( const VertexArray *vertexArray );
		static void Bind ( VertexArray *vertexArray );
		static void Unbind ( VertexArray *vertexArray ) {
			if ( IsBound ( vertexArray ) ) {
				Bind ( nullptr );
			}
		}
		
		VertexArray();
		virtual ~VertexArray();
		
		virtual bool isBound() const {
			return IsBound ( this );
		}
		
		virtual void bind() {
			Bind ( this );
		}
		
		virtual void unbind() {
			Unbind ( this );
		}
		
	};
	
}
}
}

#endif // #ifndef __JSLIB_RENDER_OPENGL_VERTEXARRAY_HPP
