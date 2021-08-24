#pragma once

namespace GLCore 
{
	class GLInitializer 
	{
	public:
		GLInitializer() = delete; 

		static bool initGL(
			const int majorVersion,
			const int minorVersion);

		static void releaseGL();
	};
}