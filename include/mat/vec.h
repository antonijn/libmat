#ifndef MAT_VEC_H
#define MAT_VEC_H

#include <stdio.h>

typedef struct {
	float x, y, z;
} vec3;

typedef struct {
	float x, y, z, w;
} vec4;

void vec3_print(vec3 v);
void vec3_println(vec3 v);
void vec3_fprint(FILE *f, vec3 v);
void vec3_fprintln(FILE *f, vec3 v);

vec3 vec3_from_vec4(vec4 v);
vec3 vec3_add(vec3 l, vec3 r);
vec3 vec3_smul(float s, vec3 v);
float vec3_normsqr(vec3 v);
float vec3_norm(vec3 v);
float vec3_dot(vec3 l, vec3 r);
vec3 vec3_cross(vec3 l, vec3 r);
vec3 vec3_normalize(vec3 v);
vec3 vec3_fast_normalize(vec3 v);

void vec4_print(vec4 v);
void vec4_println(vec4 v);
void vec4_fprint(FILE *f, vec4 v);
void vec4_fprintln(FILE *f, vec4 v);

vec4 vec4_from_vec3(vec3 v);
vec4 vec4_smul(float s, vec4 v);
float vec4_dot(vec4 l, vec4 r);

#endif

