#include "GLInitializer.h"
#include "HW17Scene.h"
#include <memory>

using namespace std;
using namespace GLCore;
using namespace Poodle;

int main()
{
    if (!GLInitializer::initGL(4, 4, GLFW_OPENGL_CORE_PROFILE))
        return -1;

    unique_ptr<GLWindow> pWindow = make_unique<GLWindow>(800, 800, "HW17");
    pWindow->bind();

    unique_ptr<HW17Scene> pScene = make_unique<HW17Scene>(*pWindow);

    pWindow->setEventHandler(*pScene);
    pWindow->startMainLoop();

    pScene.reset();
    pWindow.reset();
    
    GLInitializer::releaseGL();

    return 0;
}