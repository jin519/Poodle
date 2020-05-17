#include "ShaderProgram.h"
#include "TextureUtil.h"
#include "VertexAttributeListFactory.h"
#include "VertexArray.h"
#include "Cube.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <random>
#include <array>

using namespace std;
using namespace glm; 

static bool initGL();
static void registerCallback();
static void startMainLoop();
static void releaseGL();
static void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height);
static void keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
static void eventDispatch();
static void render();
static void render();
static void log(const string& msg);
static void setCubes();

static GLFWwindow* pWindow = nullptr;
constexpr GLuint WIDTH = 800u;
constexpr GLuint HEIGHT = 800u;

static shared_ptr<VertexArray> pVao;
static shared_ptr<ShaderProgram> pShaderProgram;
static shared_ptr<Texture2D> pTexture;

static array<Cube, 10> cubes;

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

    setCubes();
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

    pWindow = glfwCreateWindow(WIDTH, HEIGHT, "HW12", nullptr, nullptr);

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
    glEnable(GL_DEPTH_TEST);

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
        log("ESC Ű�� �����̽��ϴ�. ���α׷��� �����մϴ�.");
        glfwSetWindowShouldClose(pWindow, true);
    }

    if ((key == GLFW_KEY_ENTER) && (action == GLFW_PRESS)) 
    {
        log("���� Ű�� �����̽��ϴ�. Cube�� ���ġ�˴ϴ�.");
        setCubes();
    }
}

void eventDispatch()
{
    glfwPollEvents();
}

void render() 
{
    pShaderProgram->setUniform1i("tex", 0);

    mat4 viewMat{ 1.f };
    viewMat = translate(viewMat, vec3{ 0.f, 0.f, -50.f });
    pShaderProgram->setUniformMatrix4f("viewMat", viewMat);

    mat4 projectionMat = perspective(quarter_pi<float>(), (float(WIDTH) / float(HEIGHT)), 0.1f, 200.f);
    pShaderProgram->setUniformMatrix4f("projectionMat", projectionMat);

    const float ELAPSED_TIME = static_cast<float>(glfwGetTime());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    pTexture->activate(0);

    for (const auto& CUBE : cubes) 
    {
        mat4 modelMat{ 1.f };

        modelMat = translate(modelMat, CUBE.position);
        modelMat = rotate(modelMat, (ELAPSED_TIME * CUBE.rotationSpeed), CUBE.rotationAxis);
        modelMat = scale(modelMat, vec3{ CUBE.side });

        pShaderProgram->setUniformMatrix4f("modelMat", modelMat);

        pShaderProgram->bind();
        pVao->draw();
    }
}

void log(const string& msg)
{
    // c ǥ�� (NDEBUG: �������忡�� ���ǵȴ�.)
#ifndef NDEBUG
    cout << msg << endl;
#endif
}

void setCubes() 
{
    static default_random_engine generator;
    static const uniform_real_distribution<float> RAND_POSITION(-15.f, 15.f);
    static const uniform_real_distribution<float> RAND_SIDE(0.5f, 5.f);
    static const uniform_real_distribution<float> RAND_ROTATION_AXIS(-1.f, 1.f);
    static const uniform_real_distribution<float> RAND_ROTATION_SPEED(0.2f, 5.f);

    for (auto& cube : cubes) 
    {
        cube.position.x = RAND_POSITION(generator);
        cube.position.y = RAND_POSITION(generator);
        cube.position.z = RAND_POSITION(generator);

        cube.side = RAND_SIDE(generator);

        cube.rotationAxis.x = RAND_ROTATION_AXIS(generator);
        cube.rotationAxis.y = RAND_ROTATION_AXIS(generator);
        cube.rotationAxis.z = RAND_ROTATION_AXIS(generator);

        cube.rotationSpeed = RAND_ROTATION_SPEED(generator);
    }
}