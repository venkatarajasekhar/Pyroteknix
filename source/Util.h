// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Util
//      Game-wide utilities.
#ifndef __UTIL_H__
#define __UTIL_H__

// |----------------------------------------------------------------------------|
// |                            Framework Includes                              |
// |----------------------------------------------------------------------------|
#include <algorithm>
#include <stdio.h>
#include <stdarg.h>
#include <sps2lib.h>
#include <sps2tags.h>
#include <sps2util.h>
#include <sps2regstructs.h>
#include <assert.h>
#include <memory.h>
#include <signal.h>
#include "PS2Defines.h"
#include "ps2maths.h"
#include "ps2matrix4x4.h"
#include "pad.h"
#include "sps2wrap.h"
#include "dma.h"
#include "texture.h"
#include "font.h"
#include "pipeline.h"
#include "entities.h"
#include "vumanager.h"
#include "timer.h"
#include "ms3dmodel.h"
#include "terrain.h"
#include "audio.h"

// |----------------------------------------------------------------------------|
// |                                Constants                                   |
// |----------------------------------------------------------------------------|
enum SCREEN {SCREEN_TITLE, SCREEN_LEVEL, NUM_SCREENS, 
    SCREEN_QUIT};
const bool DEBUG = false;

	
// |----------------------------------------------------------------------------|
// |                                Functions                             		|
// |----------------------------------------------------------------------------|
void Debug(const char * strText, ...);
float Clamp(float val, float min, float max);

#endif