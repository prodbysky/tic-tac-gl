#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>
#include "ebo.h"
#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "window.h"
#include "../include/GLFW/glfw3.h"

typedef struct {
    // Resources
    shader_t shader;
    texture_t cross_texture;
    texture_t circle_texture;
    vao_t vao;
    vbo_t vbo;
    ebo_t ebo;

    // Systems
    GLFWwindow* window;

} application_t;

application_t* application_init();
void application_run(application_t* application);
void application_quit(application_t* application);

void click_callback(GLFWwindow* window, int button, int action, int mods);
#endif // APPLICATION_H
