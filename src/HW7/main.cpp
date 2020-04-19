#include "ShaderProgram.h"
#include "stb_image.h"
#include "TextureUtil.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
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
static shared_ptr<TextureBase> pTex1;
static shared_ptr<TextureBase> pTex2;
static ShaderProgram* pShaderProgram = nullptr;

static bool switch0 = true;
static bool switch1 = false;
static bool switch2 = false;

int main()
{
    if (!initGL())
        return -1;

    registerCallback();

    constexpr GLfloat vertices[] = 
    {
        // top-left
        -0.5f, 0.5f, 0.f, // pos
        1.f, 1.f, 0.f, // vert-color
        0.f, 1.f, // tex-coordinate

        // top-right
        0.5f, 0.5f, 0.f,
        0.f, 0.f, 1.f,
        1.f, 1.f, 

        // bottom-right
        0.5f, -0.5f, 0.f,
        0.f, 0.1f, 0.f,
        1.f, 0.f, 

        // bottom-left
        -0.5f, -0.5f, 0.f,
        1.f, 0.f, 0.f,
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
        8 * sizeof(float), reinterpret_cast<const void *>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), reinterpret_cast<const void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), reinterpret_cast<const void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    pTex1 = TextureUtil::createTexture2DFromImage("./res/spiral.jpg");
    pTex1->setParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    pTex1->setParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    pTex1->setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    pTex1->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    pTex2 = TextureUtil::createTexture2DFromImage("./res/explosion_anim.png");
    pTex2->setParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    pTex2->setParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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

    pWindow = glfwCreateWindow(800, 800, "HW7", nullptr, nullptr);

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
    else if ((key == GLFW_KEY_0) && (action == GLFW_PRESS))
    {
        log("0번 키를 누르셨습니다. 텍스처가 토글됩니다.");
        switch0 = !switch0;
        switch1 = false;
        switch2 = false;
    }
    else if ((key == GLFW_KEY_1) && (action == GLFW_PRESS))
    {
        log("1번 키를 누르셨습니다. 버텍스 색상이 점점 진해집니다.");
        switch1 = true;
        switch2 = false;
    }
    else if ((key == GLFW_KEY_2) && (action == GLFW_PRESS))
    {
        log("2번 키를 누르셨습니다. 텍스처 색상이 점점 진해집니다.");
        switch1 = false;
        switch2 = true;
    }
}

void eventDispatch()
{
    glfwPollEvents();
}

void updateShader() 
{
    if (switch0)
    {
        const float TIME = static_cast<float>(glfwGetTime() * 2.5f);
        const float SIN_TIME = sinf(TIME);
        const float COS_TIME = cosf(TIME);

        const mat3 MATRIX =
        (
            mat3
            {
                1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                0.5f, 0.5f, 1.f
            } *
            mat3
            {
                COS_TIME, -SIN_TIME, 0.f,
                SIN_TIME, COS_TIME, 0.f,
                0.f, 0.f, 1.f
            } *
            mat3
            {
                1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                -0.5f, -0.5f, 1.f
            }
        );

        pShaderProgram->setUniform1i("tex", 0);
        pShaderProgram->setUniformMatrix3f("matrix", MATRIX);
    }
    else 
    {
        constexpr float X_STRIDE = (1.f / 8.f);
        constexpr float Y_STRIDE = (1.f / 6.f);
        constexpr float MAX_Y_OFFSET = (1.f - Y_STRIDE);
        constexpr float MAX_X_OFFSET = (1.f - X_STRIDE); 
        constexpr float SPEED = 0.05f;

        static float timer = 0.f;
        static float xOffset = 0.f;
        static float yOffset = MAX_Y_OFFSET;
        
        timer += SPEED;

        if (timer > X_STRIDE) 
        {
            timer = 0.f;

            xOffset += X_STRIDE;

            if (xOffset > MAX_X_OFFSET)
            {
                xOffset = 0.f;
                yOffset -= Y_STRIDE;

                if (yOffset < 0.f)
                    yOffset = MAX_Y_OFFSET;
            }
        }

        const mat3 MATRIX = 
        (
            mat3
            {
                1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                xOffset, yOffset, 1.f
            } *
            mat3
            {
                X_STRIDE, 0.f, 0.f,
                0.f, Y_STRIDE, 0.f,
                0.f, 0.f, 1.f
            }
        );

        pShaderProgram->setUniform1i("tex", 1);
        pShaderProgram->setUniformMatrix3f("matrix", MATRIX);
    }

    static float mixRatio = 0.5f;

    if (switch1) 
    {
        mixRatio += 0.005f;

        if (mixRatio > 1.f)
            mixRatio = 1.f; 
    }
    else if (switch2) 
    {
        mixRatio -= 0.005f;

        if (mixRatio < 0.f)
            mixRatio = 0.f; 
    }

    pShaderProgram->setUniform1f("mixRatio", mixRatio);
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