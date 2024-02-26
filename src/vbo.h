#ifndef VBO_H
#define VBO_H

#include <stdlib.h>
#include <stdbool.h>
#include "../include/GLEW/glew.h"

typedef struct {
    GLuint ID; 
} vbo_t;

vbo_t vbo_new(void* vertices, size_t size, GLenum usage);
void vbo_bind(vbo_t vbo);
void vbo_unbind();
void vbo_delete(vbo_t vbo);

#endif // VBO_H
