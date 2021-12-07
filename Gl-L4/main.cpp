/* OpenGL libs */
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
bool push_facets = false;
bool is_cube = true;

glm::vec3 getNormalVector(GLfloat plane[]){
    int x = 0, y = 1, z = 2;
    int first = 0 * 3, second = 1 * 3, third = 2 * 3;
    glm::vec3 v1(
            plane[second + x] - plane[first + x],
            plane[second + y] -  plane[first + y],
            plane[second + z] - plane[first + z]
    );
    glm::vec3 v2(
            plane[second + x] - plane[third + x],
            plane[second + y] -  plane[third + y],
            plane[second + z] - plane[third + z]
    );
    return glm::normalize(glm::cross(v1, v2));
}
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
void drawOctahedron(GLfloat size, bool uncurtain = false)
{
    GLfloat left_top[] = {
            -size/2, 0.0f, -size / (2.0f * sqrtf(3.0f)),
            0.0f, 0.0f, size / sqrtf(3.f),
            0.0f, sqrtf(2.f)/sqrtf(3.f) * size, 0
    };
    GLfloat right_top[] = {
            size/2, 0.0f, -size / (2.0f * sqrtf(3.0f)),
            0.0f, 0.0f, size / sqrtf(3.f),
            0.0f, sqrtf(2.f)/sqrtf(3.f) * size, 0
    };
    GLfloat left_bottom[] = {
            -size/2, 0.0f, -size / (2.0f * sqrtf(3.0f)),
            0.0f, 0.0f, size / sqrtf(3.f),
            0.0f, (-1.f) * sqrtf(2.f)/sqrtf(3.f) * size, 0
    };
    GLfloat right_bottom[] = {
            size/2, 0.0f, -size / (2.0f * sqrtf(3.0f)),
            0.0f, 0.0f, size / sqrtf(3.f),
            0.0f, (-1.f) * sqrtf(2.f)/sqrtf(3.f) * size, 0
    };
    GLfloat front_top[] = {
            size/2, 0.0f, -size / (2.0f * sqrtf(3.0f)),
            -size/2, 0.0f, -size / (2.0f * sqrtf(3.0f)),
            0.0f, sqrtf(2.f)/sqrtf(3.f) * size, 0
    };
    GLfloat front_bottom[] = {
            size/2, 0.0f, -size / (2.0f * sqrtf(3.0f)),
            -size/2, 0.0f, -size / (2.0f * sqrtf(3.0f)),
            0.0f, (-1.f)*sqrtf(2.f)/sqrtf(3.f) * size, 0
    };
    if(uncurtain){
        glm::vec3 front_top_normal = -0.1f * getNormalVector(front_top);
        glm::vec3 front_bottom_normal = 0.1f * getNormalVector(front_bottom);
        glm::vec3 right_top_normal = 0.1f * getNormalVector(right_top);
        glm::vec3 left_top_normal = -0.1f * getNormalVector(left_top);
        glm::vec3 right_bottom_normal = -0.1f * getNormalVector(right_bottom);
        glm::vec3 left_bottom_normal = 0.1f * getNormalVector(left_bottom);
        for (int i = 0; i < 9; ++i){
            front_top[i] += front_top_normal[i % 3];
            front_bottom[i] += front_bottom_normal[i % 3];
            right_top[i] += right_top_normal[i % 3];
            left_top[i] += left_top_normal[i % 3];
            right_bottom[i] += right_bottom_normal[i % 3];
            left_bottom[i] += left_bottom_normal[i % 3];
        }
    }

    GLubyte ind[] = {
            0,1,2
    };
    glEnableClientState(GL_VERTEX_ARRAY);
    // левая верхняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &left_top);
    glColor3f(0.0f, 1.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);

    // правая верхняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &right_top);
    glColor3f(1.0f, 0.5f, 0.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);
    // левая нижняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &left_bottom);
    glColor3f(1.0f, 0.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);
    // правая нижняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &right_bottom);
    glColor3f(1.0f, 1.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);
    // передняя верхняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &front_top);
    glColor3f(0.0f, 0.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);
    // передняя нижняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &front_bottom);
    glColor3f(1.0f, 0.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);
    glDisableClientState(GL_VERTEX_ARRAY);
}
void checkButton (GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS){
        push_facets = ! push_facets;
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS){
        is_cube = ! is_cube;
    }
}
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 640, "Лабораторная №4", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glEnable(GL_NORMALIZE);
//    glEnable(GL_LIGHTING);
//    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//    glEnable(GL_COLOR_MATERIAL);
//    glMateriali(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    /*Initialize the GLEW library */
    if(glewInit() != GLEW_OK)
    {
        std::cout << "GLEW initialization error" << std::endl;
        return -1;
    }
    GLuint tex_name;
    glGenTextures(1, &tex_name);
    glBindTexture(GL_TEXTURE_2D, tex_name);

    int im_width, im_height, nrChannels;
    unsigned char *data = stbi_load("./corgi.png", &im_width, &im_height,
                                    &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height,
                     0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

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
        /*GLfloat light_diffuse[] = {1,0.5,1};
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
        glRotatef(3*M_PI/2.0f + angel * 20, 1,1,1);
            is_cube? drawCube(0.5, push_facets) : drawOctahedron(0.5, push_facets);
        glPopMatrix();

        glDisable(GL_LIGHT0);*/
        GLubyte ind[] = {
                0,1,2,3
        };
        GLfloat size = 0.5f;
        GLfloat front[] = {
                -size / 2, -size / 2, -size / 2,
                size / 2, -size / 2, -size / 2,
                size / 2,  size / 2, -size / 2,
                -size / 2,  size / 2, -size / 2,
        };
        GLfloat tex[] = {
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,
        };
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, &front);
            glTexCoordPointer(2, GL_FLOAT, 0, &tex);
            glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}