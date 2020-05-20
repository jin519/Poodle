#include "GLInitializer.h"
#include "HW15Scene.h"
#include <memory>

using namespace std;
using namespace GLCore;
using namespace Poodle;

int main()
{
    if (!GLInitializer::initGL(4, 4, GLFW_OPENGL_CORE_PROFILE))
        return -1;

    unique_ptr<GLWindow> pWindow = make_unique<GLWindow>(800, 800, "HW15");
    pWindow->bind();

    unique_ptr<HW15Scene> pScene = make_unique<HW15Scene>(*pWindow);

    pWindow->setEventHandler(*pScene);
    pWindow->startMainLoop();

    pScene.reset();
    pWindow.reset();
    
    GLInitializer::releaseGL();

    return 0;
}