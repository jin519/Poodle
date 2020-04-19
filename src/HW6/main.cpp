#include "ShaderProgram.h"
#include "stb_image.h"
#include "TextureUtil.h"
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

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
static shared_ptr<TextureBase> pTex1;
static shared_ptr<TextureBase> pTex2;
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
        0.f, 1.f, // tex-coordinate

        // top-right
        0.5f, 0.5f, 0.f,
        1.f, 1.f, 

        // bottom-right
        0.5f, -0.5f, 0.f,
        1.f, 0.f, 

        // bottom-left
        -0.5f, -0.5f, 0.f,
        0.f, 0.f
    };

    constexpr GLuint indices[] = 
    { 
        0, 3, 2, 1, 0, 2
    };
   
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        5 * sizeof(float), reinterpret_cast<const void *>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE,
        5 * sizeof(float), reinterpret_cast<const void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    pTex1 = TextureUtil::createTexture2DFromImage("./res/monkeys.png");
    pTex1->setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    pTex1->setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    pTex1->setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    pTex1->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    pTex2 = TextureUtil::createTexture2DFromImage("./res/floral.jpg");
    pTex2->setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    pTex2->setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    pTex2->setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    pTex2->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    pShaderProgram = new ShaderProgram("rectangle_vert.glsl", "rectangle_frag.glsl");

    startMainLoop();
    releaseGL();

    return 0;
}

bool initGL() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pWindow = glfwCreateWindow(800, 800, "HW6", nullptr, nullptr);

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
    pShaderProgram->setUniform1i("tex1", 0);
    pShaderProgram->setUniform1i("tex2", 1);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    pShaderProgram->bind();
    
    pTex1->activate(0);
    pTex2->activate(1);

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