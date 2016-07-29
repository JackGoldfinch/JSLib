/*
 * JSLib_GLM.cpp
 *
 *  Created on: 01.07.2016
 *      Author: johannes
 */

#define GLM_MESSAGES
#define JSLIB_GLM_NO_FWD
#include "JSLib_GLM.hpp"


// operator ( vecX * double )

glm::vec2 operator* ( const glm::vec2 &vec, const double scalar ) {
	return { vec.x * scalar, vec.y * scalar };
}

glm::vec3 operator* ( const glm::vec3 &vec, const double scalar ) {
	return { vec.x * scalar, vec.y * scalar, vec.z * scalar };
}

glm::vec4 operator* ( const glm::vec4 &vec, const double scalar ) {
	return { vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar };
}

// operator ( dvecX * double )

glm::dvec2 operator* ( const glm::dvec2 &vec, const double scalar ) {
	return { vec.x * scalar, vec.y * scalar };
}

glm::dvec3 operator* ( const glm::dvec3 &vec, const double scalar ) {
	return { vec.x * scalar, vec.y * scalar, vec.z * scalar };
}

glm::dvec4 operator* ( const glm::dvec4 &vec, const double scalar ) {
	return { vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar };
}


// operator << ( stream << vecX )

std::ostream &operator<< ( std::ostream &stream, const glm::vec2 &v ) {
	stream << "dvec3: r" << v.r << " g" << v.g;
	return stream;
}

std::ostream &operator<< ( std::ostream &stream, const glm::vec3 &v ) {
	stream << "dvec3: r" << v.r << " g" << v.g << " b" << v.b;
	return stream;
}

std::ostream &operator<< ( std::ostream &stream, const glm::vec4 &v ) {
	stream << "dvec3: r" << v.r << " g" << v.g << " b" << v.b << " a" << v.a;
	return stream;
}

// operator << ( stream << dvecX )

std::ostream &operator<< ( std::ostream &stream, const glm::dvec2 &v ) {
	stream << "dvec3: r" << v.r << " g" << v.g;
	return stream;
}

std::ostream &operator<< ( std::ostream &stream, const glm::dvec3 &v ) {
	stream << "dvec3: r" << v.r << " g" << v.g << " b" << v.b;
	return stream;
}

std::ostream &operator<< ( std::ostream &stream, const glm::dvec4 &v ) {
	stream << "dvec3: r" << v.r << " g" << v.g << " b" << v.b << " a" << v.a;
	return stream;
}
