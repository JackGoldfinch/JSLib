#pragma once
#ifndef __JSLIB_EXPORT_HPP
#define __JSLIB_EXPORT_HPP

#ifdef _WINDOWS

#ifdef __JSLIB_EXPORTING
#define JSLIB_EXPORT __declspec(dllexport)
#else
#define JSLIB_EXPORT __declspec(dllimport)
#endif // #ofdef __JSLIB_EXPORTING

#else

#define JSLIB_EXPORT

#endif // #ifdef _WINDOWS

#endif // #ifndef __JSLIB_EXPORT_HPP
