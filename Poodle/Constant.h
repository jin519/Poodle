#pragma once

#include <glad/glad.h>
#include <glm/gtc/constants.hpp>

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

		namespace Camera
		{
			constexpr float defaultFov{ glm::quarter_pi<float>() };
			constexpr float minFov{ glm::quarter_pi<float>() * 0.3f };
			constexpr float maxFov{ glm::half_pi<float>() };
			constexpr float defaultOrthoHeight{ 40.f };
			constexpr float maxOrthoHeight{ 400.f };
			constexpr float minOrthoHeight{ 10.f };
			constexpr float defaultAspectRatio{ 1.f };
			constexpr float defaultZNear{ 1.f };
			constexpr float defaultZFar{ 1000.f };
			constexpr float translationStep{ 10.f };
		}

		constexpr GLfloat minScale{ 0.001f };
		constexpr GLfloat maxScale{ 1000.f };
	}
}