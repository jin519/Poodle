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

    if ((key == GLFW_KEY_W) && (action == GLFW_PRESS))
    {
        cout << "[W 활성] 카메라 전진" << endl;
        __wPressed = true;
    }

    if ((key == GLFW_KEY_W) && (action == GLFW_RELEASE))
    {
        cout << "[W 해제]" << endl;
        __wPressed = false;
    }

    if ((key == GLFW_KEY_S) && (action == GLFW_PRESS))
    {
        cout << "[S 활성] 카메라 후진" << endl;
        __sPressed = true;
    }

    if ((key == GLFW_KEY_S) && (action == GLFW_RELEASE))
    {
        cout << "[S 해제]" << endl;
        __sPressed = false;
    }

    if ((key == GLFW_KEY_A) && (action == GLFW_PRESS))
    {
        cout << "[A 활성] 카메라 좌측 이동" << endl;
        __aPressed = true;
    }

    if ((key == GLFW_KEY_A) && (action == GLFW_RELEASE))
    {
        cout << "[A 해제]" << endl;
        __aPressed = false;
    }

    if ((key == GLFW_KEY_D) && (action == GLFW_PRESS))
    {
        cout << "[D 활성] 카메라 우측 이동" << endl;
        __dPressed = true;
    }

    if ((key == GLFW_KEY_D) && (action == GLFW_RELEASE))
    {
        cout << "[D 해제]" << endl;
        __dPressed = false;
    }

    if ((key == GLFW_KEY_Q) && (action == GLFW_PRESS))
    {
        cout << "[Q 활성] 카메라 하강" << endl;
        __qPressed = true;
    }

    if ((key == GLFW_KEY_Q) && (action == GLFW_RELEASE))
    {
        cout << "[Q 해제]" << endl;
        __qPressed = false;
    }

    if ((key == GLFW_KEY_E) && (action == GLFW_PRESS))
    {
        cout << "[E 활성] 카메라 상승" << endl;
        __ePressed = true;
    }

    if ((key == GLFW_KEY_E) && (action == GLFW_RELEASE))
    {
        cout << "[E 해제]" << endl;
        __ePressed = false;
    }
}

void DemoScene::onUpdate(const float deltaTime)
{
    Transform& cameraTransform = __pCamera->getTransform();
    const GLfloat TRANSLATION_STEP = (deltaTime * Constant::Camera::TRANSLATION_STEP);

    if (__wPressed)
        cameraTransform.advanceZ(-TRANSLATION_STEP);
    if (__sPressed)
        cameraTransform.advanceZ(TRANSLATION_STEP);
    if (__aPressed)
        cameraTransform.advanceX(-TRANSLATION_STEP);
    if (__dPressed)
        cameraTransform.advanceX(TRANSLATION_STEP);
    if (__qPressed)
        cameraTransform.advanceY(TRANSLATION_STEP);
    if (__ePressed)
        cameraTransform.advanceY(-TRANSLATION_STEP);

    __pCamera->update();

    for (auto& cube : __cubes) 
    {
        const float ANGLE = (deltaTime * cube.rotationSpeed);

        Transform& transform = cube.transform;
        transform.rotateLocal(ANGLE, ANGLE, ANGLE);
        transform.updateMatrix();
    }
}

void DemoScene::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    __pTexture->activate(0);

    __pShaderProgram->setUniform1i("tex", 0);
    __pShaderProgram->setUniformMatrix4f("viewMat", __pCamera->getViewMatrix());
    __pShaderProgram->setUniformMatrix4f("projectionMat", __pCamera->getProjectionMatrix());
    
    for (const auto& CUBE : __cubes)
    {
        __pShaderProgram->setUniformMatrix4f("modelMat", CUBE.transform.getModelMatrix());
        __pShaderProgram->bind();

        __pVao->draw();
    }
    
    getWindow().swapBuffers();
}

void DemoScene::onResize(const int width, const int height) 
{
    __super::onResize(width, height);
    __pCamera->setAspectRatio(width, height);
    __pCamera->update();
}

void DemoScene::onMouseButton(const int button, const int action, const int mods) 
{

}

void DemoScene::onMouseMove(const double xPos, const double yPos) 
{
    GLfloat pitch = 0.f, yaw = 0.f;

    if (__mouseMoved) 
    {
        pitch = static_cast<GLfloat>(__mouseYPos - yPos);
        yaw = static_cast<GLfloat>(__mouseXPos - xPos);
    }
    else 
    {
        pitch = static_cast<GLfloat>(__mouseYPos);
        yaw = static_cast<GLfloat>(__mouseXPos);
        __mouseMoved = true;
    }
    
    pitch *= 0.001f;
    yaw *= 0.001f;

    Transform& transform = __pCamera->getTransform();
    transform.rotateFPS(pitch, yaw);

    __mouseXPos = xPos;
    __mouseYPos = yPos;
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

    __pCamera = make_unique<PerspectiveCamera>();
    __pCamera->setNear(0.1f);
    __pCamera->setFar(200.f);
    __pCamera->getTransform().advanceZ(70.f);

    __pTexture = TextureUtil::createTexture2DFromImage("./res/container.jpg");
    __pTexture->setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    __pTexture->setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    __pTexture->setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    __pTexture->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    __pShaderProgram = make_shared<ShaderProgram>("rectangle_vert.glsl", "rectangle_frag.glsl");
    
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