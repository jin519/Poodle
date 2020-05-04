#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "stb_image.h"
#include "TextureUtil.h"
#include "VertexAttributeListFactory.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;
using namespace glm; 

static bool initGL();
static void registerCallback();
static void startMainLoop();
static void releaseGL();
static void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height);
static void keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
static void eventDispatch();
static void updateShader();
static void render();
static void log(const string& msg);

static GLFWwindow* pWindow = nullptr;
static GLuint vao;
static ShaderProgram* pShaderProgram = nullptr;

int main()
{
    if (!initGL())
        return -1;

    registerCallback();

    constexpr GLfloat vertices[] = 
    {
        // top-left
        -0.5f, 0.5f, 0.f, // pos
        1.f, 1.f, 0.f, 1.f, // vert-color

        // top-right
        0.5f, 0.5f, 0.f,
        0.f, 0.f, 1.f, 1.f,

        // bottom-right
        0.5f, -0.5f, 0.f,
        0.f, 0.1f, 0.f, 1.f,

        // bottom-left
        -0.5f, -0.5f, 0.f,
        1.f, 0.f, 0.f, 1.f
    };

    constexpr GLuint indices[] = 
    { 
        0, 3, 2, 1, 0, 2
    };
   
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBuffer vbo;
    vbo.memoryAlloc(vertices, sizeof(vertices), GL_STATIC_DRAW);

    IndexBuffer ebo;
    ebo.memoryAlloc(indices, sizeof(indices), GL_STATIC_DRAW);

    const vector<VertexAttribute>& VERTEX_ATTRIBUTES = VertexAttributeListFactory::get(VertexAttributeFlag::POS3 | VertexAttributeFlag::COLOR4);
    for (const auto& vertexAttribute : VERTEX_ATTRIBUTES) 
    {
        glVertexAttribPointer(
            vertexAttribute.location, 
            vertexAttribute.dataStructure.numElements, 
            vertexAttribute.dataStructure.elementType, 
            vertexAttribute.dataStructure.normalized,
            vertexAttribute.stride, 
            reinterpret_cast<const void*>(size_t(vertexAttribute.offset)));

        glEnableVertexAttribArray(vertexAttribute.location);
    }

    glBindVertexArray(0);

    pShaderProgram = new ShaderProgram("rectangle_vert.glsl", "rectangle_frag.glsl");

    startMainLoop();
    releaseGL();

    return 0;
}

bool initGL() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pWindow = glfwCreateWindow(800, 800, "HW9", nullptr, nullptr);

    if (!pWindow)
    {
        log("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        log("Failed to initialize GLAD");
        glfwTerminate();
        return false;
    }

    glfwSwapInterval(1); // VSYNC 0: off, 1: on

    return true;
}

void registerCallback() 
{
    glfwSetFramebufferSizeCallback(pWindow, framebufferSizeCallback);
    glfwSetKeyCallback(pWindow, keyCallback);
}

void startMainLoop() 
{
    while (!glfwWindowShouldClose(pWindow))
    {
        eventDispatch();
        updateShader();
        render();
        glfwSwapBuffers(pWindow);
    }
}

void releaseGL() 
{
    delete pShaderProgram;
    pShaderProgram = nullptr;

    glfwTerminate();
}

void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
    {
        log("ESC 키를 누르셨습니다. 프로그램을 종료합니다.");
        glfwSetWindowShouldClose(pWindow, true);
    }
}

void eventDispatch()
{
    glfwPollEvents();
}

void updateShader() 
{
    mat4 transMat = translate(mat4{ 1.f }, vec3{ 0.7f, -0.3f, 0.f });
    transMat = rotate(transMat, quarter_pi<float>(), vec3{ 0.f, 0.f, 1.f });
    transMat = scale(transMat, vec3{ 0.5f, 0.5f, 1.f });

    pShaderProgram->setUniformMatrix4f("transMat", transMat);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    pShaderProgram->bind();

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<const void*>(0));
}

void log(const string& msg)
{
    // c 표준 (NDEBUG: 릴리즈모드에서 정의된다.)
#ifndef NDEBUG
    cout << msg << endl;
#endif
}