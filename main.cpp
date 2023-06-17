#include <GLFW/glfw3.h>

#include <iostream>

#include "game.h"

#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   WINDOW_WIDTH * 3 / 4

// GLFW callbacks
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void errorCallback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::cerr << "Key: " << key << ", Action: " << action << std::endl;

    Game* gs = Game::GetInstance();
    if (action == GLFW_PRESS) gs->keys[key] = true;
    if (action == GLFW_RELEASE) gs->keys[key] = false;
}

int main() {

    // Errors
    glfwSetErrorCallback(errorCallback);

    // Graphics library initialization
    if (!glfwInit()) {
        return -1;
    }

    // Game state
    Game* gs = Game::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, 128);

    // Window and context
    GLFWwindow* window = glfwCreateWindow(gs->winWidth, gs->winHeight, "Raycast", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetWindowSizeLimits(window, gs->winWidth / 2, gs->winHeight / 2, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwMakeContextCurrent(window);

    // Wait 1 frame until swapping buffers (vsync; 0 specifies to immediately load frames)
    glfwSwapInterval(1);

    // Frame buffer and viewport sizing
    int iwidth, iheight;
    glfwGetFramebufferSize(window, &iwidth, &iheight); 
    gs->winWidth = static_cast<unsigned int>(iwidth);
    gs->winHeight = static_cast<unsigned int>(iheight);
    glViewport(0, 0, gs->winWidth, gs->winHeight);

    // Window resize callback
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  

    // All key presses go through this callback
    glfwSetKeyCallback(window, keyCallback);

    Player* player = new Player();
    gs->Init(player);

    // While window does not close, call display
    while (!glfwWindowShouldClose(window)) {
        gs->Input();
        gs->Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gs->Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
