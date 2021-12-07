/* OpenGL libs */
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
bool push_facets = false;
bool is_cube = true;
bool enable_tex = true;
GLuint  texture_names[6];

void setTextures(const std::vector<std::string>& files){
    int im_width, im_height, nrChannels;
    uint i = 0;
    for (const auto & file : files){
        glBindTexture(GL_TEXTURE_2D, texture_names[i]);
            unsigned char *data = stbi_load(file.c_str(), &im_width, &im_height,
                                            &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height,
                         0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "Failed to load texture" << std::endl;
        }
            stbi_image_free(data);
        ++i;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}
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

    GLfloat tex[] = {
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
    };
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
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
        if(enable_tex)
            glBindTexture(GL_TEXTURE_2D, texture_names[0]);
        else
            glBindTexture(GL_TEXTURE_2D, 0);
    // левая грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &left);
        glTexCoordPointer(2, GL_FLOAT, 0, &tex);
        glColor3f(0.0f, 1.0f, 0.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[1]);
    // правая грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &right);
        glColor3f(1.0f, 0.5f, 0.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[2]);
    // нижняя грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &bottom);
        glColor3f(1.0f, 0.0f, 0.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[3]);
    // верхняя грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &up);
        glColor3f(1.0f, 1.0f, 0.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[4]);
    // задняя грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &back);
        glColor3f(0.0f, 0.0f, 1.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[5]);
    // передняя грань
        glVertexPointer(3,
                        GL_FLOAT,
                        0,
                        &front);
        glColor3f(1.0f, 0.0f, 1.0f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &ind);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
void drawOctahedron(GLfloat size, bool uncurtain = false)
{
    GLfloat tex[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.5f, 1.0f
    };
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
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[0]);
    else
        glBindTexture(GL_TEXTURE_2D, 0);
    // левая верхняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &left_top);
    glTexCoordPointer(2, GL_FLOAT, 0, &tex);
    glColor3f(0.0f, 1.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[1]);
    // правая верхняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &right_top);
    glTexCoordPointer(2, GL_FLOAT, 0, &tex);
    glColor3f(1.0f, 0.5f, 0.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[2]);
    // левая нижняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &left_bottom);
    glTexCoordPointer(2, GL_FLOAT, 0, &tex);
    glColor3f(1.0f, 0.0f, 0.0f);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[3]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);
    // правая нижняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &right_bottom);
    glTexCoordPointer(2, GL_FLOAT, 0, &tex);
    glColor3f(1.0f, 1.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[4]);
    // передняя верхняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &front_top);
    glTexCoordPointer(2, GL_FLOAT, 0, &tex);
    glColor3f(0.0f, 0.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &ind);

    if(enable_tex)
        glBindTexture(GL_TEXTURE_2D, texture_names[5]);
    // передняя нижняя грань
    glVertexPointer(3,
                    GL_FLOAT,
                    0,
                    &front_bottom);
    glTexCoordPointer(2, GL_FLOAT, 0, &tex);
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
    if (key == GLFW_KEY_2 && action == GLFW_PRESS){
        enable_tex = ! enable_tex;
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
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);
    glMateriali(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    /*Initialize the GLEW library */
    if(glewInit() != GLEW_OK)
    {
        std::cout << "GLEW initialization error" << std::endl;
        return -1;
    }
    glGenTextures(6, texture_names);
    std::vector<std::string> v = {
            std::string("./corgi.png"),
            std::string("./pusheen.png"),
            std::string("./many_corgies.png"),
            std::string("./garfidl.png"),
            std::string("./owl.png"),
            std::string("./best.png")
    };
    setTextures(v);

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
        glRotatef(3*M_PI/2.0f + angel * 20, 1,1,1);
            is_cube? drawCube(0.5, push_facets) : drawOctahedron(0.5, push_facets);
        glPopMatrix();
        glDisable(GL_LIGHT0);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}