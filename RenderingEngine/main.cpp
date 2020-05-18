#include "GLInitializer.h"
#include "HW14Scene.h"
#include <memory>

using namespace std;

int main()
{
    if (!GLInitializer::initGL(4, 4, GLFW_OPENGL_CORE_PROFILE))
        return -1;

    unique_ptr<GLWindow> pWindow = make_unique<GLWindow>(800, 800, "HW14");
    pWindow->bind();

    unique_ptr<HW14Scene> pScene = make_unique<HW14Scene>(*pWindow);

    pWindow->setEventHandler(*pScene);
    pWindow->startMainLoop();

    pScene.reset();
    pWindow.reset();
    
    GLInitializer::releaseGL();

    return 0;
}