#ifndef SHADER_H
#define SHADER_H


#include <stdlib.h>
#include <stdio.h>
#include "../include/GLEW/glew.h"
#include "../include/cglm/cglm.h"

typedef struct {
    GLuint ID;
} shader_t;

shader_t shader_new(const char* vertex_shader_path, const char* fragment_shader_path);
void shader_use(shader_t shader);
void shader_delete(shader_t shader);
int shader_get_uniform_int(shader_t shader, const char* name);
void shader_set_uniform_int(shader_t shader, const char* name, int value);
void shader_set_uniform_mat4(shader_t shader, const char* name, vec4* value);

char* read_file(const char* file_path);
void check_shader_compilation(GLuint shader);

#endif // SHADER_H
