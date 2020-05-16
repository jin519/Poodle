#include "GLInitializer.h"
#include "TestScene.h"
#include <memory>

using namespace std;

int main()
{
    if (!GLInitializer::initGL(4, 4, GLFW_OPENGL_CORE_PROFILE))
        return -1;

    unique_ptr<GLWindow> pWindow = make_unique<GLWindow>(800, 800, "HW13");
    pWindow->bind();

    unique_ptr<TestScene> pScene = make_unique<TestScene>(*pWindow);

    pWindow->setEventHandler(*pScene);
    pWindow->startMainLoop();

    pWindow.release();
    pScene.release();
    
    GLInitializer::releaseGL();

    return 0;
}