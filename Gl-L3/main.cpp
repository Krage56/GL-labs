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
//    gluQuadricNormals(shape, GLU_FLAT);
    gluQuadricNormals(shape, GLU_SMOOTH);
    gluSphere(shape, radius, slices, stacks);
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 640, "Второй этап - свет", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
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

    /*Init the timer*/
    double prev = glfwGetTime();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor (1, 1, 1, 0.5);
        GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};

        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

        GLfloat light2_diffuse[] = {1, 1, 1};

        GLfloat light2_position[] = {0.0, 0.0, 0.0, 1.0};

        glEnable(GL_LIGHT0);

        glLightfv(GL_LIGHT0, GL_DIFFUSE, light2_diffuse);

        glLightfv(GL_LIGHT0, GL_POSITION, light2_position);

        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);

        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);

        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4);

        drawSolidSphere(0.5, 30, 30);

        glDisable(GL_LIGHT0);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}