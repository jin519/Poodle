#pragma once

namespace GLCore 
{
	class GLInitializer abstract final
	{
	public:
		/* static function */
		static bool initGL(
			const int renderContextVersionMajor,
			const int renderContextVersionMinor,
			const int profileMode);

		static void releaseGL();
	};
}