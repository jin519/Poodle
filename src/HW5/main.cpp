#include "ShaderProgram.h"
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
static ShaderProgram* pShaderProgram = nullptr;

static float displacement = 0.f;

static float acceleration = 0.001f;
static const float MAX_ACCELERATION = 0.5f;
static const float MIN_ACCELERATION = 0.001f;

static bool accelerationFlag = false;
static bool colorFlag = false;

int main()
{
    if (!initGL())
        return -1;

    registerCallback();

    GLfloat vertices[] = 
    {
        0.f, 0.577350259f, 0.f, // top
        1.f, 0.f, 0.f, // red

        -0.5f, -0.288675129f, 0.f, // left,
        0.f, 1.f, 0.f, // green

        0.5f, -0.288675129f, 0.f, // right
        0.f, 0.f, 1.f // blue
    };

    GLuint indices[] = 
    {  
        0, 1, 2
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
        6 * sizeof(float), reinterpret_cast<const void *>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(float), reinterpret_cast<const void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    pShaderProgram = new ShaderProgram("triangle_vert.glsl", "triangle_frag.glsl");

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

    pWindow = glfwCreateWindow(800, 800, "HW5", nullptr, nullptr);

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
    else if ((key == GLFW_KEY_SPACE) && (action == GLFW_PRESS))
    {
        log("SPACE 키를 누르셨습니다. 속도가 점진적으로 증가합니다.");
        accelerationFlag = true;
    }
    else if ((key == GLFW_KEY_SPACE) && (action == GLFW_RELEASE)) 
    {
        log("SPACE 키가 해제되었습니다. 속도가 점진적으로 감소합니다.");
        accelerationFlag = false;
    }
    else if ((key == GLFW_KEY_1) && (action == GLFW_PRESS)) 
    {
        log("1번 키를 누르셨습니다. 색상이 변경됩니다.");
        colorFlag = !colorFlag;
    }
}

void eventDispatch()
{
    glfwPollEvents();
}

void updateShader() 
{
    if (accelerationFlag)
    {
        acceleration += 0.001f;

        if (acceleration > MAX_ACCELERATION)
            acceleration = MAX_ACCELERATION;
    }
    else 
    {
        acceleration -= 0.001f;

        if (acceleration < MIN_ACCELERATION)
            acceleration = MIN_ACCELERATION;
    }

    displacement += acceleration;

    pShaderProgram->setUniform1f("displacement", displacement);
    pShaderProgram->setUniform1i("colorFlag", colorFlag);

    if (colorFlag) 
    {
        const float ACCUMULATED_TIME = static_cast<float>(glfwGetTime());
        const float COLOR = ((sinf(ACCUMULATED_TIME) + 1.f) * 0.5f);

        pShaderProgram->setUniform3f("uniformColor", COLOR, 0.f, 0.f);
    }
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    pShaderProgram->bind();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<const void*>(0));
}

void log(const string& msg)
{
    // c 표준 (NDEBUG: 릴리즈모드에서 정의된다.)
#ifndef NDEBUG
    cout << msg << endl;
#endif
}