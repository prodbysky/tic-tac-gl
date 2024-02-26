#include "ebo.h"

ebo_t ebo_new(void *indices, size_t size, GLenum usage) {
    ebo_t ebo;
    glGenBuffers(1, &ebo.ID);
    ebo_bind(ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
    return ebo;
}

void ebo_bind(ebo_t ebo) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.ID);
}

void ebo_unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ebo_delete(ebo_t ebo) {
    glDeleteBuffers(1, &ebo.ID);
}
