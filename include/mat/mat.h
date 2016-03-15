#ifndef MAT_MAT_H
#define MAT_MAT_H

#include <mat/vec.h>

typedef union {
	vec4 rows[4];
	float frows[4][4];
} mat4;

void mat4_print(const mat4 *m);
void mat4_fprint(FILE *f, const mat4 *m);

mat4 mat4_id(void);
mat4 mat4_translation(vec3 orig);
mat4 mat4_rot_x(float theta);
mat4 mat4_rot_y(float theta);
mat4 mat4_rot_z(float theta);
mat4 mat4_scale(vec3 scale);
mat4 mat4_ortho(float l, float r, float top, float bottom);

vec4 mat4_col(const mat4 *m, int c);

mat4 mat4_transpose(const mat4 *m);
mat4 mat4_mul(const mat4 *l, const mat4 *r);
mat4 mat4_compose(const mat4 *last, ...); /* list NULL-terminated */
vec4 mat4_vecmul(const mat4 *l, vec4 r);
mat4 mat4_smul(float s, const mat4 *m);

#endif
