#pragma once

#ifdef BL602
#include <bl602_glb.h>
#include <bl602_sec_eng.h>
#elif defined BL616
#include <bl616_glb.h>
#include <bl616_sec_eng.h>
#define SHA512_CAPABLE
#elif defined BL702
#include <bl702_glb.h>
#include <bl702_sec_eng.h>
#elif defined BL702L
#include <bl702l_glb.h>
#include <bl702l_sec_eng.h>
#elif defined BL808
#include <bl808_glb.h>
#include <bl808_sec_eng.h>
#define SHA512_CAPABLE
#define MD5_CAPABLE
#else
#warn "Chip not ported"
#endif
