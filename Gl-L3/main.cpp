/* OpenGL libs */
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <iostream>
#include <cmath>
#include <vector>

void drawSolidSphere(GLdouble radius, GLint slices, GLint stacks)
{
    GLUquadric *shape = gluNewQuadric();
    gluQuadricDrawStyle(shape, GLU_LINE);
//    gluQuadricDrawStyle(shape, GLU_FILL);
//    gluQuadricDrawStyle(shape, GLU_POINT);
    gluQuadricNormals(shape, GLU_FLAT);
//    gluQuadricNormals(shape, GLU_SMOOTH);
    gluSphere(shape, radius, slices, stacks);
}
void drawCube(GLfloat size)
{
    GLfloat left[] = {
            -size / 2, -size / 2, -size / 2,
            -size / 2,  size / 2, -size / 2,
            -size / 2,  size / 2,  size / 2,
            -size / 2, -size / 2,  size / 2
    };
    GLfloat right[] = {
            size / 2, -size / 2, -size / 2,
            size / 2, -size / 2,  size / 2,
            size / 2,  size / 2,  size / 2,
            size / 2,  size / 2, -size / 2,
    };
    GLfloat bottom[] = {
            -size / 2, -size / 2, -size / 2,
            -size / 2, -size / 2,  size / 2,
            size / 2, -size / 2,  size / 2,
            size / 2, -size / 2, -size / 2,
    };
    GLfloat up[] = {
            -size / 2, size / 2, -size / 2,
            -size / 2, size / 2,  size / 2,
            size / 2, size / 2,  size / 2,
            size / 2, size / 2, -size / 2,
    };
    GLfloat front[] = {
            -size / 2, -size / 2, -size / 2,
            size / 2, -size / 2, -size / 2,
            size / 2,  size / 2, -size / 2,
            -size / 2,  size / 2, -size / 2,
    };
    GLfloat back[] = {
            -size / 2, -size / 2,  size / 2,
            size / 2, -size / 2,  size / 2,
            size / 2,  size / 2,  size / 2,
            -size / 2,  size / 2,  size / 2,
    };
    GLubyte ind[] = {
            0,1,2,3
    };
    glEnableClientState(GL_VERTEX_ARRAY);
        // левая грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &left);
        glColor3f(0.0f, 1.0f, 0.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);

        // правая грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &right);
        glColor3f(1.0f, 0.5f, 0.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);
        // нижняя грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &bottom);
        glColor3f(1.0f, 0.0f, 0.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);
        // верхняя грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &up);
        glColor3f(1.0f, 1.0f, 0.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);
        // задняя грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &back);
        glColor3f(0.0f, 0.0f, 1.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);
        // передняя грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &front);
        glColor3f(1.0f, 0.0f, 1.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 640, "Второй этап - кубик", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glEnable(GL_NORMALIZE);

    /*Initialize the GLEW library */
    if(glewInit() != GLEW_OK)
    {
        std::cout << "GLEW initialization error" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor (1, 1, 1, 0.5);
//        glColor3f(0.0f, 1.0f, 0.0f);
//        drawSolidSphere(0.5, 60, 60);
        drawCube(0.5);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}