#include "vbo.h"

vbo_t vbo_new(void* vertices, size_t size, GLenum usage) {
    vbo_t vbo; 
    glGenBuffers(1, &vbo.ID);
    vbo_bind(vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
    return vbo;
}

void vbo_bind(vbo_t vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
}

void vbo_unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_enable_attribute(int index) {
    glEnableVertexAttribArray(index);
}

void vbo_delete(vbo_t vbo) {
    glDeleteBuffers(1, &vbo.ID);
}
