#include "HW17Scene.h"
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
HW17Scene::HW17Scene(GLWindow& window) : Scene(window)
{
    __init();
}

/* member function */
void HW17Scene::onKey(const int key, const int scancode, const int action, const int mods) 
{
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
    {
        cout << "ESC Ű�� �����̽��ϴ�. ���α׷��� �����մϴ�." << endl;
        getWindow().setCloseFlag(true);
    }

    if ((key == GLFW_KEY_SPACE) && (action == GLFW_PRESS))
    {
        cout << "�����̽� Ű�� �����̽��ϴ�. Cube�� ���� �������� ȸ���մϴ�." << endl;
        __setCube();
    }

    if ((key == GLFW_KEY_W) && (action == GLFW_PRESS))
    {
        cout << "W Ű�� �����̽��ϴ�. Cube�� �����մϴ�." << endl;
        __wFlag = true;
    }

    if ((key == GLFW_KEY_W) && (action == GLFW_RELEASE))
    {
        cout << "W Ű�� �����Ǿ����ϴ�." << endl;
        __wFlag = false; 
    }
    
    if ((key == GLFW_KEY_S) && (action == GLFW_PRESS))
    {
        cout << "S Ű�� �����̽��ϴ�. Cube�� �����մϴ�." << endl;
        __sFlag = true;
    }

    if ((key == GLFW_KEY_S) && (action == GLFW_RELEASE))
    {
        cout << "S Ű�� �����Ǿ����ϴ�." << endl;
        __sFlag = false;
    }

    if ((key == GLFW_KEY_D) && (action == GLFW_PRESS))
    {
        cout << "D Ű�� �����̽��ϴ�. Cube�� �������� �̵��մϴ�." << endl;
        __dFlag = true;
    }

    if ((key == GLFW_KEY_D) && (action == GLFW_RELEASE))
    {
        cout << "D Ű�� �����Ǿ����ϴ�." << endl;
        __dFlag = false;
    }

    if ((key == GLFW_KEY_A) && (action == GLFW_PRESS))
    {
        cout << "A Ű�� �����̽��ϴ�. Cube�� �������� �̵��մϴ�." << endl;
        __aFlag = true;
    }

    if ((key == GLFW_KEY_A) && (action == GLFW_RELEASE))
    {
        cout << "A Ű�� �����Ǿ����ϴ�." << endl;
        __aFlag = false;
    }

    if ((key == GLFW_KEY_E) && (action == GLFW_PRESS))
    {
        cout << "E Ű�� �����̽��ϴ�. Cube�� ���� �̵��մϴ�." << endl;
        __eFlag = true;
    }

    if ((key == GLFW_KEY_E) && (action == GLFW_RELEASE))
    {
        cout << "E Ű�� �����Ǿ����ϴ�." << endl;
        __eFlag = false;
    }

    if ((key == GLFW_KEY_Q) && (action == GLFW_PRESS))
    {
        cout << "Q Ű�� �����̽��ϴ�. Cube�� �Ʒ��� �̵��մϴ�." << endl;
        __qFlag = true;
    }

    if ((key == GLFW_KEY_Q) && (action == GLFW_RELEASE))
    {
        cout << "Q Ű�� �����Ǿ����ϴ�." << endl;
        __qFlag = false;
    }
}

void HW17Scene::onUpdate(const float deltaTime) 
{
    static float elapsedTime = 0.f;
    elapsedTime += deltaTime;

    const GLWindow& WINDOW = getWindow();
    const float WIDTH = static_cast<float>(WINDOW.getWidth());
    const float HEIGHT = static_cast<float>(WINDOW.getHeight());

    __projectionMat = perspective(quarter_pi<float>(), (WIDTH / HEIGHT), 0.1f, 200.f);

    Transform& transform = __cube.transform;

    if (__wFlag)
        transform.advanceZ(Constant::STEP);
    if (__sFlag)
        transform.advanceZ(-Constant::STEP);

    if (__dFlag)
        transform.advanceX(-Constant::STEP);
    if (__aFlag)
        transform.advanceX(Constant::STEP);

    if (__eFlag)
        transform.advanceY(Constant::STEP);
    if (__qFlag)
        transform.advanceY(-Constant::STEP);

    transform.updateMatrix();
}

void HW17Scene::onRender() 
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

void HW17Scene::__init() 
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

    __setCube();
}

void HW17Scene::__setCube() 
{
    static default_random_engine generator;
    static const uniform_real_distribution<float> RAND_ROTATION_SPEED(Constant::MIN_ANGLE, Constant::MAX_ANGLE);

    Transform& transform = __cube.transform;
    transform.setRotation({ RAND_ROTATION_SPEED(generator), RAND_ROTATION_SPEED(generator), RAND_ROTATION_SPEED(generator) });
    transform.updateMatrix();
}