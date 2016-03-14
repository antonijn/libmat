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
#include <mat/mat.h>

void mat4_print(const mat4 *m)
{
	mat4_fprint(stdout, m);
}
void mat4_fprint(FILE *f, const mat4 *m)
{
	int i;
	for (i = 0; i < 4; ++i)
		vec4_fprintln(f, m->rows[i]);
}

mat4 mat4_id(void)
{
	mat4 res;
	int i, j;
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			res.frows[i][j] = (i == j);
	return res;
}
mat4 mat4_translation(vec3 orig)
{
	mat4 res = mat4_id();
	res.frows[0][3] = -orig.x;
	res.frows[1][3] = -orig.y;
	res.frows[2][3] = -orig.z;
	return res;
}
mat4 mat4_rot_x(float theta)
{
	mat4 res = mat4_id();
	float c = cos(theta), s = sin(theta);
	res.frows[1][1] = res.frows[2][2] = c;
	res.frows[1][2] = s;
	res.frows[2][1] = -s;
	return res;
}
mat4 mat4_rot_y(float theta)
{
	mat4 res = mat4_id();
	float c = cos(theta), s = sin(theta);
	res.frows[0][0] = res.frows[2][2] = c;
	res.frows[2][0] = s;
	res.frows[0][2] = -s;
	return res;
}
mat4 mat4_rot_z(float theta)
{
	mat4 res = mat4_id();
	float c = cos(theta), s = sin(theta);
	res.frows[0][0] = res.frows[1][1] = c;
	res.frows[0][1] = s;
	res.frows[1][0] = -s;
	return res;
}

vec4 mat4_col(const mat4 *m, int c)
{
	vec4 res;
	res.x = m->frows[0][c];
	res.y = m->frows[1][c];
	res.z = m->frows[2][c];
	res.w = m->frows[3][c];
	return res;
}

mat4 mat4_transpose(const mat4 *m)
{
	mat4 res;
	int i, j;
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			res.frows[i][j] = m->frows[j][i];
	return res;
}
mat4 mat4_mul(const mat4 *l, const mat4 *r)
{
	/* rows act as columns */
	mat4 res;
	int i;
	for (i = 0; i < 4; ++i)
		res.rows[i] = mat4_vecmul(l, mat4_col(r, i));
	return mat4_transpose(&res);
}
vec4 mat4_vecmul(const mat4 *l, vec4 r)
{
	vec4 res;
	res.x = vec4_dot(l->rows[0], r);
	res.y = vec4_dot(l->rows[1], r);
	res.z = vec4_dot(l->rows[2], r);
	res.w = vec4_dot(l->rows[3], r);
	return res;
}
mat4 mat4_smul(float s, const mat4 *m)
{
	mat4 res;
	int i;
	for (i = 0; i < 4; ++i)
		res.rows[i] = vec4_smul(s, m->rows[i]);
	return res;
}

