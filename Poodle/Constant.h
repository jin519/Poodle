#pragma once

#include <glad/glad.h>

namespace Poodle 
{
	namespace Constant 
	{
		namespace AttribLocation 
		{
			constexpr GLuint position{ 0U };
			constexpr GLuint normal{ 1U };
			constexpr GLuint tangent{ 2U };
			constexpr GLuint texcoord{ 3U };
			constexpr GLuint color{ 4U };
			constexpr GLuint joints{ 5U };
			constexpr GLuint weights{ 6U };
		}

		constexpr GLfloat minScale{ 0.001f };
		constexpr GLfloat maxScale{ 1000.f };
	}
}