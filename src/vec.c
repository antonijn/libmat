/* 
 * Copyright (c) 2016, Antonie Blom
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

#include <math.h>

#include <mat/vec.h>
#include <mat/misc.h>

void vec3_print(vec3 v)
{
	vec3_fprint(stdout, v);
}
void vec3_println(vec3 v)
{
	vec3_fprintln(stdout, v);
}
void vec3_fprint(FILE *f, vec3 v)
{
	fprintf(f, "(%.2f; %.2f; %.2f)", (double)v.x, (double)v.y, (double)v.z);
}
void vec3_fprintln(FILE *f, vec3 v)
{
	vec3_fprint(f, v);
	fputc('\n', f);
}

vec3 vec3_from_vec4(vec4 v)
{
	vec3 res;
	res.x = v.x;
	res.y = v.y;
	res.z = v.z;
	return vec3_smul(v.w, res);
}
vec3 vec3_add(vec3 l, vec3 r)
{
	l.x += r.x;
	l.y += r.y;
	l.z += r.z;
	return l;
}
vec3 vec3_smul(float s, vec3 v)
{
	vec3 res;
	res.x = v.x * s;
	res.y = v.y * s;
	res.z = v.z * s;
	return res;
}
float vec3_normsqr(vec3 v)
{
	return vec3_dot(v, v);
}
float vec3_norm(vec3 v)
{
	return sqrt(vec3_normsqr(v));
}
float vec3_dot(vec3 l, vec3 r)
{
	return l.x*r.x + l.y*r.y + l.z*r.z;
}
vec3 vec3_cross(vec3 l, vec3 r)
{
	vec3 res;
	res.x = l.y*r.z - l.z*r.y;
	res.y = l.z*r.x - l.x*r.z;
	res.z = l.x*r.y - l.y*r.x;
	return res;
}
vec3 vec3_normalize(vec3 v)
{
	return vec3_smul(1.0f / vec3_norm(v), v);
}
vec3 vec3_fast_normalize(vec3 v)
{
	return vec3_smul(fast_inv_sqrt(vec3_normsqr(v)), v);
}
void vec4_print(vec4 v)
{
	vec4_fprint(stdout, v);
}
void vec4_println(vec4 v)
{
	vec4_fprintln(stdout, v);
}
void vec4_fprint(FILE *f, vec4 v)
{
	fprintf(f, "(%.2f; %.2f; %.2f; %.2f)",
	        (double)v.x, (double)v.y, (double)v.z, (double)v.w);
}
void vec4_fprintln(FILE *f, vec4 v)
{
	vec4_fprint(f, v);
	fputc('\n', f);
}

vec4 vec4_from_vec3(vec3 v)
{
	vec4 res;
	res.x = v.x;
	res.y = v.y;
	res.z = v.z;
	res.w = 1.0f;
	return res;
}

vec4 vec4_smul(float s, vec4 v)
{
	vec4 res;
	res.x = v.x * s;
	res.y = v.y * s;
	res.z = v.z * s;
	res.w = v.w * s;
	return res;
}
float vec4_dot(vec4 l, vec4 r)
{
	return l.x*r.x + l.y*r.y + l.z*r.z + l.w*r.w;
}

