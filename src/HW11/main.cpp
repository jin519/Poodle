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

static bool wFlag = false;
static bool sFlag = false;
static bool qFlag = false;
static bool eFlag = false;
static bool aFlag = false;
static bool dFlag = false;

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

    if (key == GLFW_KEY_W)
    {
        if (action == GLFW_PRESS)
        {
            log("W 키를 누르셨습니다. 씬이 가까워 집니다.");
            wFlag = true;
        }
        else if (action == GLFW_RELEASE)
        {
            log("W 키가 해제되었습니다.");
            wFlag = false;
        }
    }
    else if (key == GLFW_KEY_S)
    {
        if (action == GLFW_PRESS)
        {
            log("S 키를 누르셨습니다. 씬이 멀어집니다.");
            sFlag = true;
        }
        else if (action == GLFW_RELEASE)
        {
            log("S 키가 해제되었습니다.");
            sFlag = false;
        }
    }
    else if (key == GLFW_KEY_Q)
    {
        if (action == GLFW_PRESS)
        {
            log("Q 키를 누르셨습니다. 카메라가 아래로 이동합니다.");
            qFlag = true;
        }
        else if (action == GLFW_RELEASE)
        {
            log("Q 키가 해제되었습니다.");
            qFlag = false;
        }
    }
    else if (key == GLFW_KEY_E)
    {
        if (action == GLFW_PRESS)
        {
            log("E 키를 누르셨습니다. 카메라가 위로 이동합니다.");
            eFlag = true;
        }
        else if (action == GLFW_RELEASE)
        {
            log("E 키가 해제되었습니다.");
            eFlag = false;
        }
    }
    else if (key == GLFW_KEY_A)
    {
        if (action == GLFW_PRESS)
        {
            log("A 키를 누르셨습니다. 카메라가 왼쪽으로 이동합니다.");
            aFlag = true;
        }
        else if (action == GLFW_RELEASE)
        {
            log("A 키가 해제되었습니다.");
            aFlag = false;
        }
    }
    else if (key == GLFW_KEY_D)
    {
        if (action == GLFW_PRESS)
        {
            log("D 키를 누르셨습니다. 카메라가 오른쪽으로 이동합니다.");
            dFlag = true;
        }
        else if (action == GLFW_RELEASE)
        {
            log("D 키가 해제되었습니다.");
            dFlag = false;
        }
    }
}

void eventDispatch()
{
    glfwPollEvents();
}

void updateShader() 
{
    mat4 modelMat{ 1.f };
    mat4 viewMat{ 1.f };
    mat4 projectionMat{ 1.f };

    const float ELAPSED_TIME = static_cast<float>(glfwGetTime());
    modelMat = rotate(modelMat, ELAPSED_TIME, vec3{ 1.f, 1.f, 1.f });

    static float sceneX = 0.f;
    static float sceneY = 0.f;
    static float sceneZ = -3.f;

    if (wFlag)
    {
        sceneZ += 0.05f;

        if (sceneZ > -1.f)
            sceneZ = -1.f;
    }
    else if (sFlag)
    {
        sceneZ -= 0.05f;

        if (sceneZ < -5.f)
            sceneZ = -5.f;
    }
    else if (qFlag)
    {
        sceneY += 0.02f;

        if (sceneY > 1.f)
            sceneY = 1.f;
    }
    else if (eFlag)
    {
        sceneY -= 0.02f;

        if (sceneY < -1.f)
            sceneY = -1.f;
    }
    else if (aFlag)
    {
        sceneX += 0.02f;

        if (sceneX > 1.f)
            sceneX = 1.f;
    }
    else if (dFlag)
    {
        sceneX -= 0.02f;

        if (sceneX < -1.f)
            sceneX = -1.f;
    }

    viewMat = translate(viewMat, vec3{ sceneX, sceneY, sceneZ });
    projectionMat = perspective(quarter_pi<float>(), (float(WIDTH) / float(HEIGHT)), 0.1f, 100.f);

    pShaderProgram->setUniformMatrix4f("modelMat", modelMat);
    pShaderProgram->setUniformMatrix4f("viewMat", viewMat);
    pShaderProgram->setUniformMatrix4f("projectionMat", projectionMat);
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