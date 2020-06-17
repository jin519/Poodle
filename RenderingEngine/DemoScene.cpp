#include "DemoScene.h"
#include "VertexAttributeListFactory.h"
#include "TextureUtil.h"
#include "Constant.h"
#include <iostream>

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

    if ((key == GLFW_KEY_1) && (action == GLFW_PRESS)) 
    {
        cout << "[1 활성] global rotate mode" << endl;
        __globalRotateMode = true;
        __localRotateMode = false;
        __fpsRotateMode = false;
    }
    else if ((key == GLFW_KEY_2) && (action == GLFW_PRESS)) 
    {
        cout << "[2 활성] local rotate mode" << endl;
        __globalRotateMode = false;
        __localRotateMode = true;
        __fpsRotateMode = false;
    }
    else if ((key == GLFW_KEY_3) && (action == GLFW_PRESS)) 
    {
        cout << "[3 활성] fps rotate mode" << endl;
        __globalRotateMode = false;
        __localRotateMode = false;
        __fpsRotateMode = true;
    }

    if ((key == GLFW_KEY_INSERT) && (action == GLFW_PRESS)) 
    {
        cout << "[INSERT 활성] pitch 증가" << endl;
        __insertFlag = true; 
    }

    if ((key == GLFW_KEY_INSERT) && (action == GLFW_RELEASE))
    {
        cout << "[INSERT 해제]" << endl;
        __insertFlag = false;
    }

    if ((key == GLFW_KEY_DELETE) && (action == GLFW_PRESS))
    {
        cout << "[DELETE 활성] pitch 감소" << endl;
        __deleteFlag = true;
    }

    if ((key == GLFW_KEY_DELETE) && (action == GLFW_RELEASE))
    {
        cout << "[DELETE 해제]" << endl;
        __deleteFlag = false;
    }

    if ((key == GLFW_KEY_HOME) && (action == GLFW_PRESS))
    {
        cout << "[HOME 활성] yaw 증가" << endl;
        __homeFlag = true;
    }

    if ((key == GLFW_KEY_HOME) && (action == GLFW_RELEASE))
    {
        cout << "[HOME 해제]" << endl;
        __homeFlag = false;
    }

    if ((key == GLFW_KEY_END) && (action == GLFW_PRESS))
    {
        cout << "[END 활성] yaw 감소" << endl;
        __endFlag = true;
    }

    if ((key == GLFW_KEY_END) && (action == GLFW_RELEASE))
    {
        cout << "[END 해제]" << endl;
        __endFlag = false;
    }

    if ((key == GLFW_KEY_PAGE_UP) && (action == GLFW_PRESS))
    {
        cout << "[PAGE UP 활성] roll 증가" << endl;
        __pageUpFlag = true;
    }

    if ((key == GLFW_KEY_PAGE_UP) && (action == GLFW_RELEASE))
    {
        cout << "[PAGE UP 해제]" << endl;
        __pageUpFlag = false;
    }

    if ((key == GLFW_KEY_PAGE_DOWN) && (action == GLFW_PRESS))
    {
        cout << "[PAGE DOWN 활성] roll 감소" << endl;
        __pageDownFlag = true;
    }

    if ((key == GLFW_KEY_PAGE_DOWN) && (action == GLFW_RELEASE))
    {
        cout << "[PAGE DOWN 해제]" << endl;
        __pageDownFlag = false;
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
    static float elapsedTime = 0.f;
    elapsedTime += deltaTime;

    const GLWindow& WINDOW = getWindow();
    const float WIDTH = static_cast<float>(WINDOW.getWidth());
    const float HEIGHT = static_cast<float>(WINDOW.getHeight());

    __projectionMat = perspective(quarter_pi<float>(), (WIDTH / HEIGHT), 0.1f, 200.f);

    Transform& transform = __cube.transform;

    if (__globalRotateMode) 
    {
        if (__insertFlag) 
            transform.rotateGlobal(Constant::ANGLE_AUGEND, 0.f, 0.f);
        if (__deleteFlag)
            transform.rotateGlobal(-Constant::ANGLE_AUGEND, 0.f, 0.f);
        if (__homeFlag)
            transform.rotateGlobal(0.f, Constant::ANGLE_AUGEND, 0.f);
        if (__endFlag)
            transform.rotateGlobal(0.f, -Constant::ANGLE_AUGEND, 0.f);
        if (__pageUpFlag)
            transform.rotateGlobal(0.f, 0.f, Constant::ANGLE_AUGEND);
        if (__pageDownFlag)
            transform.rotateGlobal(0.f, 0.f, -Constant::ANGLE_AUGEND);
    }
    else if (__localRotateMode) 
    {
        if (__insertFlag)
            transform.rotateLocal(Constant::ANGLE_AUGEND, 0.f, 0.f);
        if (__deleteFlag)
            transform.rotateLocal(-Constant::ANGLE_AUGEND, 0.f, 0.f);
        if (__homeFlag)
            transform.rotateLocal(0.f, Constant::ANGLE_AUGEND, 0.f);
        if (__endFlag)
            transform.rotateLocal(0.f, -Constant::ANGLE_AUGEND, 0.f);
        if (__pageUpFlag)
            transform.rotateLocal(0.f, 0.f, Constant::ANGLE_AUGEND);
        if (__pageDownFlag)
            transform.rotateLocal(0.f, 0.f, -Constant::ANGLE_AUGEND);
    }
    else if (__fpsRotateMode) 
    {
        if (__insertFlag)
            transform.rotateFPS(Constant::ANGLE_AUGEND, 0.f);
        if (__deleteFlag)
            transform.rotateFPS(-Constant::ANGLE_AUGEND, 0.f);
        if (__homeFlag)
            transform.rotateFPS(0.f, Constant::ANGLE_AUGEND);
        if (__endFlag)
            transform.rotateFPS(0.f, -Constant::ANGLE_AUGEND);
    }

    if (__upFlag)
        transform.advanceZ(Constant::STEP);
    if (__downFlag)
        transform.advanceZ(-Constant::STEP);
    if (__rightFlag)
        transform.advanceX(Constant::STEP);
    if (__leftFlag)
        transform.advanceX(-Constant::STEP);

    transform.updateMatrix();
}

void DemoScene::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    __pTexture->activate(0);

    __pShaderProgram->setUniform1i("tex", 0);
    __pShaderProgram->setUniformMatrix4f("viewMat", __viewMat);
    __pShaderProgram->setUniformMatrix4f("projectionMat", __projectionMat);
    __pShaderProgram->setUniformMatrix4f("modelMat", __cube.transform.getModelMatrix());

    __pShaderProgram->bind();
    __pVao->draw();

    getWindow().swapBuffers();
}

void DemoScene::__init()
{
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

    __viewMat = translate(__viewMat, vec3{ 0.f, 0.f, -10.f });
}