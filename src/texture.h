#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdbool.h>

#include "../include/GLEW/glew.h"
#include "../include/stb_image.h"

typedef struct {
    GLuint ID;
} texture_t;

texture_t texture_new(const char *file_path, int slot);
void texture_activate(int slot);
void texture_bind(texture_t texture);
void texture_unbind();
void texture_delete(texture_t texture);

#endif // TEXTURE_H
