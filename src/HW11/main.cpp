#include "ShaderProgram.h"
#include "TextureUtil.h"
#include "VertexAttributeListFactory.h"
#include "VertexArray.h"
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
constexpr GLuint WIDTH = 800u;
constexpr GLuint HEIGHT = 800u;

static shared_ptr<VertexArray> pVao;
static shared_ptr<ShaderProgram> pShaderProgram;
static shared_ptr<Texture2D> pTexture;

int main()
{
    if (!initGL())
        return -1;

    registerCallback();

    constexpr GLfloat vertices[] = 
    {
        // top
        // 0 (top left)
        -0.5f, 0.5f, 0.5f, // position
        0.f, 1.f,          // tex-coordinate
        // 1 (top right)
        0.5f, 0.5f, 0.5f,
        1.f, 1.f,
        // 2 (bottom right)
        0.5f, 0.5f, -0.5f,
        1.f, 0.f,
        // 3 (bottom left)
        -0.5f, 0.5f, -0.5f,
        0.f, 0.f,

        // bottom
        // 4 (top left) 
        -0.5f, -0.5f, 0.5f,
        0.f, 1.f,
        // 5 (top right)
        0.5f, -0.5f, 0.5f, 
        1.f, 1.f,
        // 6 (bottom right)
        0.5f, -0.5f, -0.5f, 
        1.f, 0.f,
        // 7 (bottom left)
        -0.5f, -0.5f, -0.5f,
        0.f, 0.f, 

        // left
        // 8 (3) 
        -0.5f, 0.5f, -0.5f,
        0.f, 1.f,
        // 9 (0)
        -0.5f, 0.5f, 0.5f, 
        1.f, 1.f,          
        // 10 (4)
        -0.5f, -0.5f, 0.5f,
        1.f, 0.f,
        // 11 (7)
        -0.5f, -0.5f, -0.5f,
        0.f, 0.f,

        // right
        // 12 (2) 
        0.5f, 0.5f, -0.5f,
        0.f, 1.f,
        // 13 (1) 
        0.5f, 0.5f, 0.5f,
        1.f, 1.f,
        // 14 (5) 
        0.5f, -0.5f, 0.5f,
        1.f, 0.f,
        // 15 (6) 
        0.5f, -0.5f, -0.5f,
        0.f, 0.f,

        // front
        // 16 (3)
        -0.5f, 0.5f, -0.5f,
        0.f, 1.f,
        // 17 (2) 
        0.5f, 0.5f, -0.5f,
        1.f, 1.f,
        // 18 (6) 
        0.5f, -0.5f, -0.5f,
        1.f, 0.f,
        // 19 (7) 
        -0.5f, -0.5f, -0.5f,
        0.f, 0.f,

        // back
        // 20 (0)
        -0.5f, 0.5f, 0.5f,
        0.f, 1.f,
        // 21 (1) 
        0.5f, 0.5f, 0.5f,
        1.f, 1.f,
        // 22 (5) 
        0.5f, -0.5f, 0.5f,
        1.f, 0.f,
        // 23 (4)
        -0.5f, -0.5f, 0.5f,
        0.f, 0.f
    };

    constexpr GLuint indices[] = 
    { 
        0, 3, 2, 0, 2, 1,       // top
        4, 7, 6, 4, 6, 5,       // bottom
        8, 10, 9, 8, 11, 10,    // left
        12, 14, 13, 12, 15, 14, // right
        16, 18, 17, 16, 19, 18, // front
        20, 22, 21, 20, 23, 22 // back
    };

    pVao = make_shared<VertexArray>(
        VertexAttributeListFactory::get(VertexAttributeFlag::POS3 | VertexAttributeFlag::TEXCOORD2),
        make_shared<VertexBuffer>(vertices, sizeof(vertices), GL_STATIC_DRAW),
        make_shared<IndexBuffer>(indices, sizeof(indices), GL_STATIC_DRAW),
        static_cast<GLsizei>(size(vertices)));

    pTexture = TextureUtil::createTexture2DFromImage("./res/container.jpg");

    pTexture->setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    pTexture->setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    pTexture->setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    pTexture->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    pShaderProgram = make_shared<ShaderProgram>("rectangle_vert.glsl", "rectangle_frag.glsl");

    glEnable(GL_DEPTH_TEST);

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

    pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Coordinate Systems", nullptr, nullptr);

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
    pVao.reset();
    pShaderProgram.reset();

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
    mat4 modelMat{ 1.f };

    const float ELAPSED_TIME = static_cast<float>(glfwGetTime());
    modelMat = rotate(modelMat, ELAPSED_TIME, vec3{ 1.f, 1.f, 1.f });

    pShaderProgram->setUniformMatrix4f("modelMat", modelMat);
    pShaderProgram->setUniform1i("tex", 0);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pShaderProgram->bind();
    pTexture->activate(0);
    pTexture->bind();

    pVao->draw();
}

void log(const string& msg)
{
    // c 표준 (NDEBUG: 릴리즈모드에서 정의된다.)
#ifndef NDEBUG
    cout << msg << endl;
#endif
}