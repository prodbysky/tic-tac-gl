#include "vao.h"

vao_t vao_new() {
    vao_t vao;
    glGenVertexArrays(1, &vao.ID);
    return vao;
}

void vao_bind(vao_t vao) {
    glBindVertexArray(vao.ID);
}

void vao_unbind() {
    glBindVertexArray(0);
}

void vao_delete(vao_t vao) {
    glDeleteVertexArrays(1, &vao.ID);
}

void vao_add_attribute(vbo_t vbo, int index, int component_count, GLenum type, bool normalized, int stride, void *begin) {
    vbo_bind(vbo);
    glVertexAttribPointer(index, component_count, type, normalized, stride, begin);
    vbo_unbind();
}

void vao_enable_attribute(int index) {
    glEnableVertexAttribArray(index);
}
