/* Copyright (c) 2016, Antonie Blom
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef MAT_MISC_H
#define MAT_MISC_H

#include <math.h>
#include <mat/vec.h>

#if __STDC_VERSION__ < 199901L
#define inline
#endif

#define M_TAU (2 * M_PI)

#define deg_to_rad(x) (x * (M_PI / 180.0f))
#define rad_to_deg(x) (x * (180.0f / M_PI))

static inline vec3 VEC3(float x, float y, float z)
{
	vec3 res;
	res.x = x;
	res.y = y;
	res.z = z;
	return res;
}

static inline vec4 VEC4(float x, float y, float z, float w)
{
	vec4 res;
	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return res;
}

static inline float fast_inv_sqrt(float x)
{
	union {
		float f;
		int i;
	} i;
	float half = x * 0.5f;
	i.f = x;
	/* newton-raphson guess, assumes arithmetic right shift */
	i.i = 0x5F375A86 - (i.i >> 1);
	x = i.f;
	return x * (1.5f - half * x * x);
}

#ifdef inline
#undef inline
#endif

#endif
