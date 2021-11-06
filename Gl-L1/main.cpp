/* OpenGL libs */
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <iostream>
#include <cmath>
#include <vector>

void drawCircle(float x, float y, float r, int amountSegments, const std::vector<float>& color){
    float l = 0.1;еше
    float _x = 0, _y = 0;
    float a = M_PI * 2 / amountSegments;
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(color[0],color[1],color[2]);
        glVertex2f(x,y);
        for(int i = -1; i < amountSegments; ++i)
        {
            _x = x + sinf(a * i) * l;
            _y = y + cosf(a * i) * l;
            glVertex2f(_x,_y);
        }
    glEnd();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 640, "Летний хутор", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*Initialize the GLEW library */
    if(glewInit() != GLEW_OK)
    {
        std::cout << "GLEW initialization error" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    /*Init the timer*/
    double prev = glfwGetTime();
    std::vector<float> sunPos({-0.9, 0.3});
    float r = 0.1;
    std::vector<float> moonPos({-0.7, -0.3});
    float aleph = 0;
    float light = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        /* Render here */
        glClearColor(light, light, light, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0, 1, 0);
        glBegin(GL_QUADS);
            glVertex2f(-1, -1);
            glVertex2f(-1, -0.75);
            glVertex2f(1, -0.75);
            glVertex2f(1, -1);
        glEnd();
        glColor3f(1, 0, 0);
        glBegin(GL_QUADS);
            glVertex2f(0, -0.8);
            glVertex2f(0, -0.4);
            glVertex2f(0.5, -0.4);
            glVertex2f(0.5, -0.8);
        glEnd();
        glColor3f(0.4, 0.4, 0);
        glBegin(GL_TRIANGLES);
            glVertex2f(0, -0.4);
            glVertex2f(0.25, -0.2);
            glVertex2f(0.5f, -0.4);
        glEnd();
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
            glVertex2f(0.2, -0.65);
            glVertex2f(0.2, -0.55);
            glVertex2f(0.35, -0.55);
            glVertex2f(0.35, -0.65);
        glEnd();
        /*Hand-made animation*/
        if(glfwGetTime() - prev >= 1/20){
            aleph -= 1;
            glPushMatrix();
                glTranslatef(0, -0.9, 0);
                glRotatef(aleph, 0, 0, 1);
                glTranslatef(0, 1.2, 0);
                drawCircle(moonPos[0], moonPos[1], r, 250, std::vector<float>({1,1,1}));
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0, -0.7, 0);
                glRotatef(aleph, 0, 0, 1);
                glTranslatef(2, 0, 0);
                drawCircle(sunPos[0], sunPos[1], r, 250, std::vector<float>({1,1,0}));
            glPopMatrix();
            prev = glfwGetTime();
            light = sinf(aleph / 180 * M_PI);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}