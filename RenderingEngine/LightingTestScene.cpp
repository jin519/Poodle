#include "LightingTestScene.h"
#include "VertexAttributeListFactory.h"
#include "TextureUtil.h"
#include "Constant.h"
#include <iostream>
#include <random>

using namespace std;
using namespace glm;
using namespace GLCore;
using namespace Poodle;

vec3 prevPointLightPosition = { -0.7f, -0.3f, 0.f };
vec3 pointLightPosition = { 0.f, -0.3f, 0.f };
vec3 centerPosition = { 0.f, -0.3f, 0.f };
const float RADIUS = length(prevPointLightPosition - centerPosition);

/* constructor */
LightingTestScene::LightingTestScene(GLWindow& window) : Scene(window) 
{
	__init();
}

/* member function */
void LightingTestScene::onKey(const int key, const int scancode, const int action, const int mods) 
{
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
    {
        cout << "[ESC 활성] 프로그램 종료" << endl;
        getWindow().setCloseFlag(true);
    }

    if ((key == GLFW_KEY_SPACE) && (action == GLFW_PRESS))
    {
        cout << "[SPACE] 마우스 커서 토글" << endl;
        __mouseCursor = !__mouseCursor;
        showMouseCursor(__mouseCursor);
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

void LightingTestScene::onUpdate(const float deltaTime) 
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
        cameraTransform.advanceY(-TRANSLATION_STEP);
    if (__ePressed)
        cameraTransform.advanceY(TRANSLATION_STEP);

    static float elapsedTime = 0.f;
    elapsedTime += deltaTime;

    pointLightPosition.x = (RADIUS * cosf(elapsedTime));
    pointLightPosition.z = (RADIUS * sinf(elapsedTime));

    __pCamera->update();
}

void LightingTestScene::onRender() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    __pShaderProgram->setUniform3f("material.ambient", 0.2f, 0.2f, 0.2f);
    __pShaderProgram->setUniform3f("material.diffuse", .6f, .6f, 0.6f);
    __pShaderProgram->setUniform3f("material.specular", .7f, .7f, .7f);
    __pShaderProgram->setUniform1f("material.shininess", 80.f);
    __pShaderProgram->setUniform1ui("light.type", 1u);
    __pShaderProgram->setUniform3f("light.position", pointLightPosition.x, pointLightPosition.y, pointLightPosition.z);
    __pShaderProgram->setUniform3f("light.ambient", 0.7f, 0.2f, 0.2f);
    __pShaderProgram->setUniform3f("light.diffuse", 0.5f, 0.1f, 0.1f);
    __pShaderProgram->setUniform3f("light.specular", 1.f, 0.5f, 0.5f);

    const vec3 DIRECTION = normalize(vec3(-1.f, -1.f, -1.f));
    __pShaderProgram->setUniform3f("light.direction", DIRECTION.x, DIRECTION.y, DIRECTION.z);

    const vec4 CAMERA_DIRECTION = __pCamera->getTransform().getBasisZ();
    __pShaderProgram->setUniform3f("camera.direction", CAMERA_DIRECTION.x, CAMERA_DIRECTION.y, CAMERA_DIRECTION.z);

    __pShaderProgram->setUniformMatrix4f("viewMat", __pCamera->getViewMatrix());
    __pShaderProgram->setUniformMatrix4f("projectionMat", __pCamera->getProjectionMatrix());
    __pShaderProgram->bind();
    
    __pVao->draw();

    getWindow().swapBuffers();
}

void LightingTestScene::onResize(const int width, const int height) 
{
    __super::onResize(width, height);
    __pCamera->setAspectRatio(width, height);
}

void LightingTestScene::onMouseButton(const int button, const int action, const int mods) 
{
    
}

void LightingTestScene::onMouseMove(const double xPos, const double yPos) 
{
    if (!__mouseMoved)
    {
        __mouseXPos = xPos;
        __mouseYPos = yPos;
        __mouseMoved = true;
    }

    const GLfloat PITCH = (static_cast<GLfloat>(__mouseYPos - yPos) * 0.002f);
    const GLfloat YAW = (static_cast<GLfloat>(__mouseXPos - xPos) * 0.002f);

    Transform& transform = __pCamera->getTransform();
    transform.rotateFPS(PITCH, YAW);

    __mouseXPos = xPos;
    __mouseYPos = yPos;
}

void LightingTestScene::onScroll(const double delta) 
{
    __pCamera->adjustFov(-(static_cast<float>(delta) * 0.03f));
}

void LightingTestScene::__init() 
{
    showMouseCursor(false);

    glfwSwapInterval(1); // VSYNC 0: off, 1: on
    glEnable(GL_DEPTH_TEST);

    constexpr GLfloat vertices[] =
    {
        // 0 (top left)
        -1.f, -.5f, 1.f, // position
        0.f, 1.f, 0.f, // normal
        // 1 (top right)
        1.f, -.5f, 1.f,
        0.f, 1.f, 0.f, 
        // 2 (bottom right)
        1.f, -.5f, -1.f,
        0.f, 1.f, 0.f,
        // 3 (bottom left)
        -1.f, -.5f, -1.f,
        0.f, 1.f, 0.f,
    };

    constexpr GLuint indices[] =
    {
        0, 3, 2, 0, 2, 1
    };

    __pVao = make_shared<VertexArray>(
        VertexAttributeListFactory::get(VertexAttributeFlag::POS3 | VertexAttributeFlag::NORMAL3),
        make_shared<VertexBuffer>(vertices, sizeof(vertices), GL_STATIC_DRAW),
        make_shared<IndexBuffer>(indices, sizeof(indices), GL_STATIC_DRAW),
        static_cast<GLsizei>(size(vertices)));

    __pCamera = make_unique<PerspectiveCamera>();
    __pCamera->setNear(0.1f);
    __pCamera->setFar(200.f);
    __pCamera->getTransform().setPosition(0.f, 2.f, 2.f);
    __pCamera->getTransform().rotateGlobal(-.9f, 0.f, 0.f);

    __pShaderProgram = make_shared<ShaderProgram>("lighting_test_rectangle_vert.glsl", "lighting_test_rectangle_frag.glsl");
    __pShaderProgram->setUniformMatrix4f("modelMat", mat4{ 1.f });
}