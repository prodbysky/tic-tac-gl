#ifndef EBO_H
#define EBO_H

#include <stdlib.h>
#include "../include/GLEW/glew.h"

typedef struct {
    GLuint ID;
} ebo_t;

ebo_t ebo_new(void* indices, size_t size, GLenum usage);
void ebo_bind(ebo_t ebo);
void ebo_unbind();
void ebo_delete(ebo_t ebo);

#endif // EBO_H
