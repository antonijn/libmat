#ifndef MAT_MISC_H
#define MAT_MISC_H

#include <math.h>
#include <mat/vec.h>

#define M_TAU (2 * M_PI)

#define deg_to_rad(x) (x * (M_PI / 180.0f))
#define rad_to_deg(x) (x * (180.0f / M_PI))

static vec3 VEC3(float x, float y, float z)
{
	vec3 res;
	res.x = x;
	res.y = y;
	res.z = z;
	return res;
}

static vec4 VEC4(float x, float y, float z, float w)
{
	vec4 res;
	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return res;
}

float fast_inv_sqrt(float x);

#endif
