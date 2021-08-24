#include "../Poodle/GLInitializer.h"

using namespace GLCore; 

int main() 
{
	if (!GLInitializer::initGL(4, 6))
		return -1; 

	return 0; 
}