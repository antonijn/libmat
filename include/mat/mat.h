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

#ifndef MAT_MAT_H
#define MAT_MAT_H

#if __STDV_VERSION__ < 199901L
#define inline
#endif

#include <mat/vec.h>

#include <math.h>
#include <stdarg.h>

#include <mat/vec.h>
#include <mat/mat.h>

typedef union {
	vec4 cols[4];
	float fcols[4][4];
	float floats[16];
} mat4;

static inline void mat4_print(const mat4 *m)
{
	mat4_fprint(stdout, m);
}
static inline void mat4_fprint(FILE *f, const mat4 *m)
{
	int i;
	for (i = 0; i < 4; ++i)
		vec4_fprintln(f, mat4_row(m, i));
}

static inline mat4 mat4_id(void)
{
	mat4 res;
	res.cols[0].x = 1.0f;
	res.cols[0].y = res.cols[0].z = res.cols[0].w = 0.0f;
	res.cols[1].y = 1.0f;
	res.cols[1].x = res.cols[0].z = res.cols[0].w = 0.0f;
	res.cols[2].z = 1.0f;
	res.cols[2].x = res.cols[0].y = res.cols[0].w = 0.0f;
	res.cols[3].w = 1.0f;
	res.cols[3].x = res.cols[0].y = res.cols[0].z = 0.0f;
	return res;
}
static inline mat4 mat4_translation(vec3 orig)
{
	mat4 res = mat4_id();
	res.cols[3].x = -orig.x;
	res.cols[3].y = -orig.y;
	res.cols[3].z = -orig.z;
	return res;
}
static inline mat4 mat4_rot_yz(float c, float s)
{
	mat4 res = mat4_id();
	res.fcols[1][1] = res.fcols[2][2] = c;
	res.fcols[2][1] = s;
	res.fcols[1][2] = -s;
	return res;
}
static inline mat4 mat4_rot_x(float theta)
{
	return mat4_rot_yz(cos(theta), sin(theta));
}
static inline mat4 mat4_rot_xz(float c, float s)
{
	mat4 res = mat4_id();
	res.fcols[0][0] = res.fcols[2][2] = c;
	res.fcols[0][2] = s;
	res.fcols[2][0] = -s;
	return res;
}
static inline mat4 mat4_rot_y(float theta)
{
	return mat4_rot_xz(cos(theta), sin(theta));
}
static inline mat4 mat4_rot_xy(float c, float s)
{
	mat4 res = mat4_id();
	res.fcols[0][0] = res.fcols[1][1] = c;
	res.fcols[1][0] = s;
	res.fcols[0][1] = -s;
	return res;
}
static inline mat4 mat4_rot_z(float theta)
{
	return mat4_rot_xy(cos(theta), sin(theta));
}
static inline mat4 mat4_scale(vec3 scale)
{
	mat4 res = mat4_id();
	res.cols[0].x = scale.x;
	res.cols[1].y = scale.y;
	res.cols[2].z = scale.z;
	return res;
}
static inline mat4 mat4_ortho(float l, float r, float top, float bottom)
{
	vec3 orig1, orig2, scalev;
	mat4 trans1, scale, trans2, res;
	float w, h;

	w = r - l;
	h = top - bottom;

	orig1.x = l;
	orig1.y = bottom;
	orig1.z = 0.0f;
	trans1 = mat4_translation(orig1);

	scalev.x = 2.0f / w;
	scalev.y = 2.0f / h;
	scalev.z = 1.0f;
	scale = mat4_scale(scalev);

	orig2.x = 1.0f;
	orig2.y = 1.0f;
	orig2.z = 0.0f;
	trans2 = mat4_translation(orig2);

	return mat4_compose(&trans2, &scale, &trans1, NULL);
}
static inline mat4 mat4_persp_fov(float fov, float aspect, float near, float far)
{
	mat4 res = { 0 };
	float y_scale = 1.0f / tan(fov / 2);
	float x_scale = y_scale / aspect;
	res.fcols[0][0] = x_scale;
	res.fcols[1][1] = y_scale;
	res.fcols[2][2] = (-near - far) / (near - far);
	res.fcols[2][3] = 1.0f;
	res.fcols[3][2] = 2 * near * far / (near - far);
	return res;
}
static inline mat4 mat4_lookat(vec3 cam, vec3 at)
{
	vec3 diff;
	mat4 rot_xz, rot_uy;
	mat4 res = mat4_translation(cam);
	double xz_len, inv_xz_len, inv_uy_len;

	diff = vec3_sub(at, cam);
	xz_len = sqrt(diff.x*diff.x + diff.z*diff.z);
	if (xz_len > 0.0) {
		inv_xz_len = 1.0 / xz_len;
		diff.x *= inv_xz_len;
		diff.z *= inv_xz_len;

		rot_xz = mat4_rot_xz(diff.x, diff.z);
		res = mat4_mul(&rot_xz, &res);
	}
	inv_uy_len = 1.0 / sqrt(xz_len*xz_len + diff.y*diff.y);
	diff.y *= inv_uy_len;
	xz_len *= inv_uy_len;
	rot_uy = mat4_rot_yz(diff.y, xz_len);
	res = mat4_mul(&rot_uy, &res);

	return res;
}

static inline vec4 mat4_row(const mat4 *m, int c)
{
	vec4 res;
	res.x = m->fcols[0][c];
	res.y = m->fcols[1][c];
	res.z = m->fcols[2][c];
	res.w = m->fcols[3][c];
	return res;
}

static inline mat4 mat4_transpose(const mat4 *m)
{
	mat4 res;
	int i, j;
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			res.fcols[i][j] = m->fcols[j][i];
	return res;
}
static inline mat4 mat4_mul(const mat4 *l, const mat4 *r)
{
	mat4 res;
	int i, j;

	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			res.fcols[i][j] = vec4_dot(mat4_row(l, j), r->cols[i]);

	return res;
}
static inline mat4 mat4_compose(const mat4 *last, ...)
{
	va_list ap;
	mat4 res = *last;
	va_start(ap, last);

	while (last = va_arg(ap, const mat4 *))
		res = mat4_mul(&res, last);

	va_end(ap);
	return res;
}
static inline vec4 mat4_vecmul(const mat4 *l, vec4 r)
{
	vec4 res;
	res.x = vec4_dot(mat4_row(l, 0), r);
	res.y = vec4_dot(mat4_row(l, 1), r);
	res.z = vec4_dot(mat4_row(l, 2), r);
	res.w = vec4_dot(mat4_row(l, 3), r);
	return res;
}
static inline mat4 mat4_smul(float s, const mat4 *m)
{
	mat4 res;
	int i;
	for (i = 0; i < 4; ++i)
		res.cols[i] = vec4_smul(s, m->cols[i]);
	return res;
}

#ifdef inline
#undef inline
#endif

#endif
