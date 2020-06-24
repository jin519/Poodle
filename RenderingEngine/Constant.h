#pragma once

namespace Poodle 
{
	namespace Constant
	{
		constexpr float MIN_SCALE = 0.001f;
		constexpr float MAX_SCALE = 1000.f;

		// cube setting
		constexpr float MIN_ANGLE = 0.2f;
		constexpr float MAX_ANGLE = 0.5f;
		constexpr float ANGLE_AUGEND = 0.05f;
		constexpr float STEP = 0.05f;
	}

	namespace Constant::Camera 
	{
		constexpr float DEFAULT_ORTHO_HEIGHT = 40.f;
		constexpr float MAX_ORTHO_HEIGHT = 400.f;
		constexpr float MIN_ORTHO_HEIGHT = 10.f;
		constexpr float DEFAULT_ASPECT_RATIO = 1.f;
		constexpr float DEFAULT_Z_NEAR = 1.f;
		constexpr float DEFAULT_Z_FAR = 1000.f;
	}
}