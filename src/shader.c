#include "shader.h"
#include <stdio.h>

shader_t shader_new(const char *vertex_shader_path, const char *fragment_shader_path) {
    shader_t shader;
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_shader_source = read_file(vertex_shader_path);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    check_shader_compilation(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_shader_source = read_file(fragment_shader_path);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    check_shader_compilation(fragment_shader);

    shader.ID = glCreateProgram();

    glAttachShader(shader.ID, vertex_shader);
    glAttachShader(shader.ID, fragment_shader);
    glLinkProgram(shader.ID);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader;
}

void shader_use(shader_t shader) {
    glUseProgram(shader.ID);
}

void shader_delete(shader_t shader) {
    glDeleteProgram(shader.ID);
}

int shader_get_uniform_int(shader_t shader, const char *name) {
    GLint uniform_location = glGetUniformLocation(shader.ID, name);

    if (uniform_location == -1) {
        fprintf(stderr, "[WARNING]: Requested to get non-existent uniform %s\n", name);
        return -1;
    }

    int uniform;
    shader_use(shader);
    glGetUniformiv(shader.ID, uniform_location, &uniform);
    return uniform;
}

void shader_set_uniform_int(shader_t shader, const char *name, int value) {
    GLint uniform_location = glGetUniformLocation(shader.ID, name);

    if (uniform_location == -1) {
        fprintf(stderr, "[WARNING]: Requested to set non-existent uniform %s\n", name);
        return;
    }

    shader_use(shader);
    glUniform1i(uniform_location, value);
}

void shader_set_uniform_mat4(shader_t shader, const char *name, vec4* value) {
    GLint uniform_location = glGetUniformLocation(shader.ID, name);

    if (uniform_location == -1) {
        fprintf(stderr, "[WARNING]: Requested to set non-existent uniform %s\n", name);
        return;
    }

    shader_use(shader);
    glUniformMatrix4fv(uniform_location, 1, GL_FALSE, &value[0][0]);
}
char* read_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* string = malloc(sizeof(char) * file_size + 1);
    string[file_size] = 0;
    fread(string, file_size, sizeof(char), file);
    return string;
}

void check_shader_compilation(GLuint shader) {
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        GLsizei len = 0;
        char log[1024];
        glGetShaderInfoLog(shader, 1024, &len, log);
        fprintf(stderr, "[ERROR]: %s\n", log);
    }
}
