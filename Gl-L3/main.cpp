/* OpenGL libs */
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>

bool push_cube_facets = false;

void drawSkeletSphere(GLdouble radius, GLint slices, GLint stacks)
{
    GLUquadric *shape = gluNewQuadric();
    gluQuadricDrawStyle(shape, GLU_LINE);
    gluQuadricNormals(shape, GLU_FLAT);
    gluSphere(shape, radius, slices, stacks);
}
void drawCube(GLfloat size, bool uncurtain = false)
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
    if(uncurtain){
        glm::vec3 front_normal(0, 0, - 0.1f);
        glm::vec3 back_normal(0, 0, 0.1f);
        glm::vec3 right_normal(0.1f, 0,0);
        glm::vec3 left_normal(-0.1f, 0,0);
        glm::vec3 up_normal(0, 0.1f, 0);
        glm::vec3 bottom_normal(0, -0.1f, 0);
        for (int i = 0; i < 12; ++i){
            front[i] += front_normal[i % 3];
            back[i] += back_normal[i % 3];
            right[i] += right_normal[i % 3];
            left[i] += left_normal[i % 3];
            up[i] += up_normal[i % 3];
            bottom[i] += bottom_normal[i % 3];
        }
    }

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
void checkButton (GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS){
        push_cube_facets = ! push_cube_facets;
    }
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
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);
    glMateriali(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 0);
    glEnable(GL_DEPTH_TEST);
    /*Initialize the GLEW library */
    if(glewInit() != GLEW_OK)
    {
        std::cout << "GLEW initialization error" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    GLfloat angel = 0.0f;
    double prev = glfwGetTime();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLfloat light_diffuse[] = {1,0.5,1};
        if(glfwGetTime() - prev >= 1.0f/20){
            angel += (M_PI / 100.0f);
            prev = glfwGetTime();
        }
        glEnable(GL_LIGHT0);
        GLfloat light_pos[3];
        light_pos[0] = 0.7 * cosf(angel);
        light_pos[1] = 0.0f;
        light_pos[2] = 0.7 * sinf(angel);
        glfwSetKeyCallback(window, checkButton);
        glPushMatrix();
            glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
            GLfloat test[] = {0.0f,0.0f,0.0f, 0.8f};
            glTranslatef(light_pos[0], light_pos[1], light_pos[2]);
            glLightfv(GL_LIGHT0, GL_POSITION, test);
            glColor3f(1.0f, 1.0f, 1.0f);
            drawSkeletSphere(0.1, 20, 20);
        glPopMatrix();

        glPushMatrix();
            glRotatef(3*M_PI/2.0f + angel * 10, 1,1,1);
            drawCube(0.5, push_cube_facets);
        glPopMatrix();


        /* Swap front and back buffers */
        glDisable(GL_LIGHT0);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}