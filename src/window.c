#include "window.h"

GLFWwindow* window_new(int w, int h, char* title) {
    glfwInit();

    // Tell OpenGL to use OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(w, h, title, NULL, NULL);

    if (window == NULL) {
        return NULL;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    GLenum glew_ok = glewInit();

    if (glew_ok != GLEW_OK) {
        fprintf(stderr, "[ERROR]: %s", glewGetErrorString(glew_ok));
        return 0;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    stbi_set_flip_vertically_on_load(true);

    // Area where OpenGL will render to
    glViewport(0, 0, w, h);

    return window;
}
