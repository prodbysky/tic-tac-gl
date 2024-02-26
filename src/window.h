#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdbool.h>

#include "../include/GLEW/glew.h"
#include "../include/GLFW/glfw3.h"

#include "../include/stb_image.h"

GLFWwindow* window_new(int w, int h, char* title);

#endif // WINDOW_H
