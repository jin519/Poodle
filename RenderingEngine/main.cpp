#include "GLInitializer.h"
#include "DemoScene.h"
#include <memory>

using namespace std;
using namespace GLCore;
using namespace Poodle;

int main()
{
    if (!GLInitializer::initGL(4, 4, GLFW_OPENGL_CORE_PROFILE))
        return -1;

    unique_ptr<GLWindow> pWindow = make_unique<GLWindow>(800, 800, "HW18");
    pWindow->bind();

    unique_ptr<DemoScene> pScene = make_unique<DemoScene>(*pWindow);

    pWindow->setEventHandler(*pScene);
    pWindow->startMainLoop();

    pScene.reset();
    pWindow.reset();
    
    GLInitializer::releaseGL();

    return 0;
}