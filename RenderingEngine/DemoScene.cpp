#include "DemoScene.h"
#include "VertexAttributeListFactory.h"
#include "TextureUtil.h"
#include "Constant.h"
#include <iostream>
#include <random>

using namespace std;
using namespace glm;
using namespace GLCore;
using namespace Poodle;

/* constructor */
DemoScene::DemoScene(GLWindow& window) : Scene(window)
{
    __init();
}

/* member function */
void DemoScene::onKey(const int key, const int scancode, const int action, const int mods)
{
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
    {
        cout << "[ESC 활성] 프로그램 종료" << endl;
        getWindow().setCloseFlag(true);
    }

    if ((key == GLFW_KEY_UP) && (action == GLFW_PRESS))
    {
        cout << "[UP 활성] forward 기준으로 전진" << endl;
        __upFlag = true;
    }

    if ((key == GLFW_KEY_UP) && (action == GLFW_RELEASE))
    {
        cout << "[UP 해제]" << endl;
        __upFlag = false;
    }

    if ((key == GLFW_KEY_DOWN) && (action == GLFW_PRESS))
    {
        cout << "[DOWN 활성] forward 기준으로 후진" << endl;
        __downFlag = true;
    }

    if ((key == GLFW_KEY_DOWN) && (action == GLFW_RELEASE))
    {
        cout << "[DOWN 해제]" << endl;
        __downFlag = false;
    }

    if ((key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS))
    {
        cout << "[RIGHT 활성] HORIZONTAL 기준으로 우측 이동" << endl;
        __rightFlag = true;
    }

    if ((key == GLFW_KEY_RIGHT) && (action == GLFW_RELEASE))
    {
        cout << "[RIGHT 해제]" << endl;
        __rightFlag = false;
    }

    if ((key == GLFW_KEY_LEFT) && (action == GLFW_PRESS))
    {
        cout << "[LEFT 활성] HORIZONTAL 기준으로 좌측 이동" << endl;
        __leftFlag = true;
    }

    if ((key == GLFW_KEY_LEFT) && (action == GLFW_RELEASE))
    {
        cout << "[LEFT 해제]" << endl;
        __leftFlag = false;
    }
}

void DemoScene::onUpdate(const float deltaTime)
{
    const GLWindow& WINDOW = getWindow();
    const float WIDTH = static_cast<float>(WINDOW.getWidth());
    const float HEIGHT = static_cast<float>(WINDOW.getHeight());

    __projectionMat = perspective(quarter_pi<float>(), (WIDTH / HEIGHT), 0.1f, 200.f);

    for (auto& cube : __cubes) 
    {
        Transform& transform = cube.transform;
        const float ANGLE = (deltaTime * cube.rotationSpeed);

        transform.rotateLocal(ANGLE, ANGLE, ANGLE);

        if (__upFlag)
            transform.advanceZ(Constant::Cube::TRANSLATION_STEP);
        if (__downFlag)
            transform.advanceZ(-Constant::Cube::TRANSLATION_STEP);
        if (__rightFlag)
            transform.advanceX(Constant::Cube::TRANSLATION_STEP);
        if (__leftFlag)
            transform.advanceX(-Constant::Cube::TRANSLATION_STEP);

        transform.updateMatrix();
    }
}

void DemoScene::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    __pTexture->activate(0);

    __pShaderProgram->setUniform1i("tex", 0);
    __pShaderProgram->setUniformMatrix4f("viewMat", __viewMat);
    __pShaderProgram->setUniformMatrix4f("projectionMat", __projectionMat);
    
    for (const auto& CUBE : __cubes)
    {
        __pShaderProgram->setUniformMatrix4f("modelMat", CUBE.transform.getModelMatrix());
        __pShaderProgram->bind();

        __pVao->draw();
    }
    
    getWindow().swapBuffers();
}

void DemoScene::onMouseButton(const int button, const int action, const int mods) 
{

}

void DemoScene::onMouseMove(const double xPos, const double yPos) 
{
    
}

void DemoScene::__init()
{
    showMouseCursor(false);

    glfwSwapInterval(1); // VSYNC 0: off, 1: on
    glEnable(GL_DEPTH_TEST);

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

    __pVao = make_shared<VertexArray>(
        VertexAttributeListFactory::get(VertexAttributeFlag::POS3 | VertexAttributeFlag::TEXCOORD2),
        make_shared<VertexBuffer>(vertices, sizeof(vertices), GL_STATIC_DRAW),
        make_shared<IndexBuffer>(indices, sizeof(indices), GL_STATIC_DRAW),
        static_cast<GLsizei>(size(vertices)));

    __pTexture = TextureUtil::createTexture2DFromImage("./res/container.jpg");
    __pTexture->setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    __pTexture->setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    __pTexture->setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    __pTexture->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    __pShaderProgram = make_shared<ShaderProgram>("rectangle_vert.glsl", "rectangle_frag.glsl");
    __viewMat = translate(__viewMat, vec3{ 0.f, 0.f, -70.f });
    
    __createCubes();
}

void DemoScene::__createCubes() 
{
    static default_random_engine generator;
    static const uniform_real_distribution<float> RAND_POSITION(-20.f, 20.f);
    static const uniform_real_distribution<float> RAND_SIDE(0.5f, 5.f);
    static const uniform_real_distribution<float> RAND_ROTATION_AXIS(-1.f, 1.f);
    static const uniform_real_distribution<float> RAND_ROTATION_SPEED(0.2f, 5.f);

    for (auto& cube : __cubes)
    {
        Transform& transform = cube.transform;

        transform.setPosition(
            RAND_POSITION(generator), 
            RAND_POSITION(generator),
            RAND_POSITION(generator));

        transform.setScale(RAND_SIDE(generator));

        transform.orient({
            RAND_ROTATION_AXIS(generator),
            RAND_ROTATION_AXIS(generator),
            RAND_ROTATION_AXIS(generator)});

        cube.rotationSpeed = RAND_ROTATION_SPEED(generator);
    }
}