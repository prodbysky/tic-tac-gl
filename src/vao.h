#ifndef VAO_H
#define VAO_H

#include "../include/GLEW/glew.h"

#include "vbo.h"

typedef struct {
    GLuint ID;
} vao_t;

vao_t vao_new();
void vao_bind(vao_t vao);
void vao_unbind();
void vao_delete(vao_t vao);
void vao_add_attribute(vbo_t vbo, int index, int component_size, GLenum type, bool normalized, int stride, void* begin);
void vao_enable_attribute(int index);

#endif // VAO_H
