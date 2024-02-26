#include "application.h"
#include <stdbool.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900
#define WINDOW_TITLE "Tic-Tac-Toe"

static GLfloat quad_vertices[] = {
     0,            WINDOW_HEIGHT, 1.0f, 0.0f, 0.0f, // Bottom left
     WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1.0f, 0.0f, // Bottom right
     0,            0,             1.0f, 0.0f, 1.0f, // Top left
     WINDOW_WIDTH, 0,             1.0f, 1.0f, 1.0f,  // Top right
};
static GLint quad_indices[] = {
    0, 1, 2, // Top triangle
    2, 3, 1,  // Bottom triangle
};

static int board[3][3] = {
    {0, 0, 0}, // 2
    {0, 0, 0}, // 1
    {0, 0, 0}  // 0
};
static int turn = 1;

bool check_for_win() {
    for (int y = 0; y < 3; y++) {
        if ((board[y] == (int[]){1, 1, 1}) || board[y] == (int[]){2, 2, 2}) {
            return true;
        }
    }
    for (int x = 0; x < 3; x++) {
        if ((board[2][x] == board[1][x]) && (board[1][x] == board[0][x]) && board[1][x] != 0) {
            return true;
        }
    }

    if ((board[2][0] == board[1][1]) && (board[1][1] == board[0][2]) && board[1][1] != 0) {
        return true;
    }
    if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][2]) && board[1][1] != 0) {
        return true;
    }
    return false;
}

application_t* application_init() {
    application_t* application = (application_t*) malloc(sizeof(application_t));
    
    application->window = window_new(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");

    if (application->window == NULL) {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        return NULL;
    }

    application->cross_texture = texture_new("resources/cross.png", 0);
    application->circle_texture = texture_new("resources/circle.png", 1);
    
    texture_activate(0);
    texture_bind(application->cross_texture);
    texture_activate(1);
    texture_bind(application->circle_texture);

    application->shader = shader_new("resources/vertex.glsl", "resources/fragment.glsl");

    application->vao = vao_new();
    application->vbo = vbo_new(quad_vertices, sizeof(quad_vertices), GL_STATIC_DRAW);
    application->ebo = ebo_new(quad_indices, sizeof(quad_indices), GL_STATIC_DRAW);

    vao_bind(application->vao);
    vbo_bind(application->vbo);
    ebo_bind(application->ebo);

    vao_add_attribute(application->vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    vao_add_attribute(application->vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    vao_enable_attribute(0);
    vao_enable_attribute(1);
    
    vbo_unbind();
    vao_unbind();
    ebo_unbind();

    glfwSetMouseButtonCallback(application->window, click_callback);


    return application;
}

void application_run(application_t* application) {

    mat4 projection;
    glm_ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1.0f, 1.0f, projection);

    while (!glfwWindowShouldClose(application->window)) {
        glClearColor(0.8f, 0.7f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                // World space center
				float cellCenterX = (x + 0.5f) * (WINDOW_WIDTH / 3.0f);
				float cellCenterY = (y + 0.5f) * (WINDOW_HEIGHT / 3.0f);

				mat4 model;
				glm_mat4_identity(model);
				glm_translate(model, (vec3){cellCenterX, cellCenterY, 0.0f});
				glm_translate(model, (vec3){-0.5f * (WINDOW_WIDTH / 3.0f), -0.5f * (WINDOW_HEIGHT / 3.0f), 0.0f});
				glm_scale(model, (vec3){0.33f, 0.33f, 1.0f});


                mat4 mvp;
                glm_mat4_mul(projection, model, mvp);

                shader_set_uniform_mat4(application->shader, "u_MVP", mvp);

                if (board[y][x] == 0) {
                    continue;
                }
                shader_set_uniform_int(application->shader, "tex0", board[y][x] - 1);
                vao_bind(application->vao);
                ebo_bind(application->ebo);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }

        if (check_for_win()) {
            if (turn == 1) {
                printf("CIRCLE WON!\n");
                return;
            }
            else {
                printf("CROSS WON!\n");
            }
            return;
        }
        glfwSwapBuffers(application->window);
        glfwWaitEvents();
    }
}

void application_quit(application_t *application) {
    vao_delete(application->vao);
    vbo_delete(application->vbo);
    ebo_delete(application->ebo);
    texture_delete(application->cross_texture);
    texture_delete(application->circle_texture);
    shader_delete(application->shader);
    glfwDestroyWindow(application->window);
    glfwTerminate();
}

void click_callback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    ypos = WINDOW_HEIGHT - ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int x = ((int)xpos - ((int)xpos % 10)) / 300;
        int y = ((int)ypos - ((int)ypos % 10)) / 300;
        if (board[y][x] != 0) {
            return;
        }
        board[y][x] = turn;
        if (turn == 1) {
            turn = 2;
            return;
        }
        turn = 1;
    }
}
