//
//  JSLib_FFMPEG.hpp
//  JSLib
//
//  Created by Johannes Stieglitz on 29.05.16.
//  Copyright © 2016 Johannes Stieglitz. All rights reserved.
//

#pragma once
#ifndef __JSLIB_FFMPEG_HPP
#define __JSLIB_FFMPEG_HPP

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
#include <libswresample/swresample.h>
}

#endif // #ifndef __JSLIB_FFMPEG_HPP
