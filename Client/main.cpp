#include "../GLCore/GLInitializer.h"
#include "DemoScene.h"

using namespace std; 
using namespace GLCore; 

int main() 
{
	if (!GLInitializer::initGL(4, 6))
		return -1; 

	unique_ptr<GLWindow> pWindow = make_unique<GLWindow>(800, 800, "Poodle 0.0.3");
	pWindow->bind(); 

	unique_ptr<DemoScene> pScene = make_unique<DemoScene>(*pWindow); 

	pWindow->setEventHandler(*pScene); 
	pWindow->startMainLoop(); 

	pScene.reset(); 
	pWindow.reset(); 

	GLInitializer::releaseGL(); 

	return 0; 
}