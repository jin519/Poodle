#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "TextReader.h"

using namespace std;

static bool initGL();
static void registerCallback();
static void createVertices(float* const pVertices);
static void startMainLoop();
static void releaseGL();
static void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height);
static void keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
static void eventDispatch();
static void render();
static void log(const string& msg);

static GLFWwindow* pWindow = nullptr;
static GLuint vao;
static GLuint shaderProgram;
constexpr int VERTEX_SIZE = 180;

int main()
{
    if (!initGL())
        return -1;

    registerCallback();

    float vertices[VERTEX_SIZE] = { 0.f };
    createVertices(vertices);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), reinterpret_cast<const void *>(0));

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const string &vertexShaderSource = TextReader::read("triangle_vert.glsl");
    const char* const pRawVertexShaderSource = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &pRawVertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);

        log(infoLog);
        glfwTerminate();

        return -1;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const string& fragShaderSource = TextReader::read("triangle_frag.glsl");
    const char* const pRawFragShaderSource = fragShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &pRawFragShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);

        log(infoLog);
        glfwTerminate();

        return -1;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) 
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
        
        log(infoLog);
        glfwTerminate();

        return -1;
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    vertexShader = 0U;

    glDeleteShader(fragmentShader);
    fragmentShader = 0U;

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

    pWindow = glfwCreateWindow(600, 600, "HW2", nullptr, nullptr);

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

void createVertices(float* const pVertices) 
{
    constexpr float RADIUS = 0.5f;
    constexpr float THICKNESS = 0.3f;
    constexpr float ANGLE = 2.f;
    constexpr int SECTOR = 18;

    const float INNER_RADIUS = (RADIUS - THICKNESS);
    const int COUNT = (VERTEX_SIZE / SECTOR);
    const float UNIT_ANGLE = (ANGLE / static_cast<float>(COUNT));

    for (int i = 0; i < COUNT; ++i)
    {
        const int OFFSET = (i * SECTOR);
        const float LEFT_ANGLE = (i * UNIT_ANGLE);
        const float RIGHT_ANGLE = (LEFT_ANGLE + UNIT_ANGLE);

        // 0 
        pVertices[OFFSET] = (RADIUS * sinf(LEFT_ANGLE));
        pVertices[OFFSET + 1] = (RADIUS * cosf(LEFT_ANGLE));
        pVertices[OFFSET + 2] = 0.f;

        // 1
        pVertices[OFFSET + 3] = (INNER_RADIUS * sinf(LEFT_ANGLE));
        pVertices[OFFSET + 4] = (INNER_RADIUS * cosf(LEFT_ANGLE));
        pVertices[OFFSET + 5] = 0.f;
        
        // 2
        pVertices[OFFSET + 6] = (RADIUS * sinf(RIGHT_ANGLE));
        pVertices[OFFSET + 7] = (RADIUS * cosf(RIGHT_ANGLE));
        pVertices[OFFSET + 8] = 0.f;

        // 3
        pVertices[OFFSET + 9] = pVertices[OFFSET + 6];
        pVertices[OFFSET + 10] = pVertices[OFFSET + 7];
        pVertices[OFFSET + 11] = 0.f;

        // 4
        pVertices[OFFSET + 12] = pVertices[OFFSET + 3];
        pVertices[OFFSET + 13] = pVertices[OFFSET + 4];
        pVertices[OFFSET + 14] = 0.f;

        // 5
        pVertices[OFFSET + 15] = (INNER_RADIUS * sinf(RIGHT_ANGLE));
        pVertices[OFFSET + 16] = (INNER_RADIUS * cosf(RIGHT_ANGLE));
        pVertices[OFFSET + 17] = 0.f;
    }
}

void startMainLoop() 
{
    while (!glfwWindowShouldClose(pWindow))
    {
        eventDispatch();
        render();
        glfwSwapBuffers(pWindow);
    }
}

void releaseGL() 
{
    glfwTerminate();
}

void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, true);
        log("ESC 키를 누르셨습니다.");
    }
}

void eventDispatch()
{
    glfwPollEvents();
}

void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_SIZE);
}

void log(const string& msg)
{
    // c 표준 (NDEBUG: 릴리즈모드에서 정의된다.)
#ifndef NDEBUG
    cout << msg << endl;
#endif
}