#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "util.h"

#define WIDTH       1024
#define HEIGHT      512
#define WIDTH_MIN   512
#define HEIGHT_MIN  256
#define WIDTH_MAX   GLFW_DONT_CARE
#define HEIGHT_MAX  GLFW_DONT_CARE

#define PI 3.1415926535
#define DR 0.0174533

int winWidth, winHeight;
float px, py, pdx, pdy, pa;
bool keyStates[512];

// Callbacks
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void errorCallback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) keyStates[key] = true;
    if (action == GLFW_RELEASE) keyStates[key] = false;
}

void keyOperations() {
    if (keyStates[GLFW_KEY_W]) {
        px += pdx;
        py += pdy;
    }
    if (keyStates[GLFW_KEY_A]) {
        pa -= 0.1;
        if (pa < 0) {
            pa += 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
    if (keyStates[GLFW_KEY_S]) {
        px -= pdx;
        py -= pdy;
    }
    if (keyStates[GLFW_KEY_D]) {
        pa += 0.1;
        if (pa > 2 * PI) {
            pa -= 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }

}

void initDisplay() {
    // Background
    glClearColor(0.30f, 0.30f, 0.35f, 0.00f);
    
    // Window-sized orthogonal viewing area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, winWidth, winHeight, 0, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);

    // Player
    px = 600, py = 600, pa = PI / 2;
    pdx = cos(pa) * 5, pdy = sin(pa) * 5;
}

void drawPlayer() {
    glColor3f(1, 1, 0);
    glPointSize(16);

    glBegin(GL_POINTS);
    glVertex2f(px, py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px + pdx * 10, py + pdy * 10);
    glEnd();
}

// map
int mapX = 8, mapY = 8, mapS = 128;
int map[] =
{
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1
};

void drawMap2D() {
    int x, y, xo, yo;
    for (y = 0; y < mapY; ++y) {
        for (x = 0; x < mapX; ++x) {
            if (map[y * mapX + x] == 1) {
                glColor3f(1, 1, 1);
            } else {
                glColor3f(0, 0, 0);
            }
            xo = x * mapS; yo = y * mapS;
            glBegin(GL_QUADS);
            glVertex2i(xo, yo);
            glVertex2i(xo, yo + mapS);
            glVertex2i(xo + mapS, yo + mapS);
            glVertex2i(xo + mapS, yo);
            glEnd();
        }
    }
}

float dist(float ax, float ay, float bx, float by, float ang) {
    return sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

void drawRays3D() {
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, disT;

    ra = pa - 30 * DR;
    if (ra < 0) {
        ra += 2 * PI;
    }
    if (ra > 2 * PI) {
        ra -= 2 * PI;
    }

    for (r = 0; r < 60; ++r) {
        // Horizontal
        dof = 0;
        float disH = INT_MAX;
        float hx = px, hy = py;
        float nrtan = -1 / tan(ra);

        if (ra > PI) {
            ry = ((int)py / 128) * 128 - 0.0001;
            rx = (py - ry) * nrtan + px;
            yo = -128;
            xo = -yo * nrtan;
        } else if (ra < PI) {
            ry = ((int)py / 128) * 128 + 128;
            rx = (py - ry) * nrtan + px;
            yo = 128;
            xo = -yo * nrtan;
        } else if (ra == 0 || ra == PI) {
            rx = px;
            ry = py;
            dof = 8;
        }

        while (dof < 8) {
            mx = (int)rx / 128;
            my = (int)ry / 128;
            mp = my * mapX + mx;
            if (0 < mp && mp < mapX * mapY && map[mp] == 1) {
                hx = rx;
                hy = ry;
                disH = dist(px, py, hx, hy, ra);
                dof = 8;
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        // Vertical
        dof = 0;
        float disV = INT_MAX;
        float vx = px, vy = py;
        float ntan = -tan(ra);

        if (ra > PI / 2 && ra < 3 * PI / 2) {
            rx = (int)px / 128 * 128 - 0.0001;
            ry = (px - rx) * ntan + py;
            xo = -128;
            yo = -xo * ntan;
        } else if (ra < PI / 2 || ra > 3 * PI / 2) {
            rx = (int)px / 128 * 128 + 128;
            ry = (px - rx) * ntan + py;
            xo = 128;
            yo = -xo * ntan;
        } else if (ra == 0 || ra == PI) {
            ry = py;
            rx = px;
            dof = 8;
        }

        while (dof < 8) {
            mx = (int)rx / 128;
            my = (int)ry / 128;
            mp = my * mapX + mx;
            if (0 < mp && mp < mapX * mapY && map[mp] == 1) {
                vx = rx;
                vy = ry;
                disV = dist(px, py, vx, vy, ra);
                dof = 8;
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        if (disV < disH) {
            rx = vx;
            ry = vy;
            disT = disV;
            glColor3f(0.9, 0, 0);
        } else {
            rx = hx;
            ry = hy;
            disT = disH;
            glColor3f(0.7, 0, 0);
        }

        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();

        // 3D walls
        float ca = pa - ra;
        if (ca < 0) {
            ca += 2 * PI;
        }
        if (ca > 2 * PI) {
            ca -= 2 * PI;
        }
        disT = disT * cos(ca); // fisheye fix
        float lineH = (mapS * HEIGHT) / disT * 2; // line height
        if (lineH > HEIGHT * 2) {
            lineH = HEIGHT * 2;
        }
        float lineO = HEIGHT - lineH / 2; // line offset
        glLineWidth(16);
        glBegin(GL_LINES);
        glVertex2i(r * 16 + WIDTH, lineO);
        glVertex2i(r * 16 + WIDTH, lineH + lineO);
        glEnd();

        ra += DR;
        if (ra < 0) {
            ra += 2 * PI;
        }
        if (ra > 2 * PI) {
            ra -= 2 * PI;
        }
    }
}

void display(GLFWwindow* window) {
    keyOperations();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawMap2D();
    drawPlayer();
    drawRays3D();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main() {

    // All errors go through this callback
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        return -1;
    }

    // Window and context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Glurblestomp", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetWindowSizeLimits(window, WIDTH_MIN, HEIGHT_MIN, WIDTH_MAX, HEIGHT_MAX);
    glfwMakeContextCurrent(window);

    // Wait 1 frame until swapping buffers (vsync; 0 specifies to immediately load frames)
    glfwSwapInterval(1);

    // Frame buffer and viewport sizing
    glfwGetFramebufferSize(window, &winWidth, &winHeight);
    glViewport(0, 0, winWidth, winHeight);

    // Window resize callback
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  

    // All key presses go through this callback
    glfwSetKeyCallback(window, keyCallback);

    initDisplay();

    // While window does not close, call display
    while (!glfwWindowShouldClose(window)) {
        display(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
