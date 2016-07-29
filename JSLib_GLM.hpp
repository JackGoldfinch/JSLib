//
//  JSLib_GLM.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 30.05.2016.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_GLM_HPP
#define __JSLIB_GLM_HPP

#define GLM_SWIZZLE
#define GLM_FORCE_SIZE_T_LENGTH

#include <iostream>

#ifdef __JSLIB_GLM_NO_FWD

#include <glm/fwd.hpp>

#else

#include <glm/glm.hpp>

#endif // #ifndef __JSLIB_GLM_NO_FWD

#include <boost/mpl/vector.hpp>

namespace glm {
	
	typedef vec3 color3;
	typedef vec4 color4;
	
	typedef boost::mpl::vector<glm::ivec2, glm::ivec3, glm::ivec4, glm::vec2, glm::vec3, glm::vec4, glm::dvec2, glm::dvec3, glm::dvec4> VectorTypes;
	typedef boost::mpl::vector<glm::ivec2, glm::ivec3, glm::ivec4> IntVectorTypes;
	typedef boost::mpl::vector<glm::vec2, glm::vec3, glm::vec4> FloatVectorTypes;
	typedef boost::mpl::vector<glm::dvec2, glm::dvec3, glm::dvec4> DoubleVectorTypes;
	
} // namespace glm

glm::vec2 operator* ( const glm::vec2 &vec, const double scalar );
glm::vec3 operator* ( const glm::vec3 &vec, const double scalar );
glm::vec4 operator* ( const glm::vec4 &vec, const double scalar );

glm::dvec2 operator* ( const glm::dvec2 &vec, const double scalar );
glm::dvec3 operator* ( const glm::dvec3 &vec, const double scalar );
glm::dvec4 operator* ( const glm::dvec4 &vec, const double scalar );


std::ostream &operator<< ( std::ostream &stream, const glm::vec2 &v );
std::ostream &operator<< ( std::ostream &stream, const glm::vec3 &v );
std::ostream &operator<< ( std::ostream &stream, const glm::vec4 &v );

std::ostream &operator<< ( std::ostream &stream, const glm::dvec2 &v );
std::ostream &operator<< ( std::ostream &stream, const glm::dvec3 &v );
std::ostream &operator<< ( std::ostream &stream, const glm::dvec4 &v );

#endif // __JSLIB_GLM_HPP
