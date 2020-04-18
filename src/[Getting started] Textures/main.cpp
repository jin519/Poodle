#include "ShaderProgram.h"
#include "stb_image.h"
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
GLuint texture1;
GLuint texture2;
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
        1.f, 0.f, 0.f, // vert-color
        0.f, 1.f, // tex-coordinate

        // top-right
        0.5f, 0.5f, 0.f,
        0.f, 1.f, 0.f, 
        1.f, 1.f, 

        // bottom-right
        0.5f, -0.5f, 0.f,
        0.f, 0.f, 1.f,
        1.f, 0.f, 

        // bottom-left
        -0.5f, -0.5f, 0.f,
        1.f, 1.f, 0.f,
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

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* pImg = stbi_load("./res/container.png", &width, &height, &nrChannels, 0);

    if (!pImg) 
    {
        log("이미지 로드에 실패하였습니다.");
        return -1;
    }

    // 1. 텍스처 오브젝트 생성
    glGenTextures(1, &texture1);
    glGenTextures(1, &texture2);

    // 2. 텍스처 바인드
    glBindTexture(GL_TEXTURE_2D, texture1);

    GLenum format;
    switch (nrChannels)
    {
    case 1:
        format = GL_RED;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
    }

    // 3. 텍스처 메모리 할당(GPU 전송)
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pImg);
    glGenerateMipmap(GL_TEXTURE_2D);

    //// 이 경우 추가적으로 border 색까지 입력해 주어야 한다.
    //GLfloat textureBorderColor[] =
    //{
    //    1.f, 0.f, 0.f, 1.f
    //};
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, textureBorderColor);

    // 4. 텍스처 파라미터 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    stbi_image_free(pImg);
    pImg = nullptr;

    /////////////////////// 텍스처 2

    glBindTexture(GL_TEXTURE_2D, texture2);

    pImg = stbi_load("./res/floral.jpg", &width, &height, &nrChannels, 0);

    if (!pImg)
    {
        log("이미지 로드에 실패하였습니다.");
        return -1;
    }

    switch (nrChannels)
    {
    case 1:
        format = GL_RED;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pImg);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    stbi_image_free(pImg);
    pImg = nullptr;

    /////////////////////// 텍스처 2 끝

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

    // VSYNC 0: off, 1: on
    glfwSwapInterval(1);

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

    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glActiveTexture(GL_TEXTURE1);

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