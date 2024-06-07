#include <iostream>
#include <vector>
// NOTE: temporary
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "FieldView.h"
#include "TextRenderer.h"
#include "TextObject.h"
#include "Shader.h"
#include "constants.h"

// Использование вектора типа double здесь неоправданно. Лишняя память.
const char* WINDOW_TITLE = "TicTacToe Tournament";
int flag = 0;

// NOTE: temporary func to set values in field.
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    flag = 1;
}

int main(void) {
    srand(time(0));
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    if (glewInit() != GLEW_OK)
        return -1;

    FieldView field;
    field.init();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0.25f, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        field.draw();

        glfwSwapBuffers(window);

        glfwPollEvents();

        if (flag) {
            flag = 0;

            if (rand() % 10000 > 3500)
                field.setTurn('x', rand() % FIELD_SIZE, rand() % FIELD_SIZE);
            else
                field.setTurn('o', rand() % FIELD_SIZE, rand() % FIELD_SIZE);
        }
    }

    glfwTerminate();
    return 0;
}
